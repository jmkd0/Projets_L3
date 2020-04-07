/***************************************************************************
 *   Copyright (C) 2006-2009 by Peter Penz <peter.penz19@gmail.com>        *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA            *
 ***************************************************************************/

#include "informationpanel.h"

#include "informationpanelcontent.h"

#include <KIO/Job>
#include <KIO/JobUiDelegate>
#include <KJobWidgets>
#include <KDirNotify>
#include <KLocalizedString>

#include <Baloo/FileMetaDataWidget>

#include <QApplication>
#include <QShowEvent>
#include <QVBoxLayout>
#include <QTimer>
#include <QMenu>

#include "dolphin_informationpanelsettings.h"

InformationPanel::InformationPanel(QWidget* parent) :
    Panel(parent),
    m_initialized(false),
    m_infoTimer(nullptr),
    m_urlChangedTimer(nullptr),
    m_resetUrlTimer(nullptr),
    m_shownUrl(),
    m_urlCandidate(),
    m_invalidUrlCandidate(),
    m_fileItem(),
    m_selection(),
    m_folderStatJob(nullptr),
    m_content(nullptr)
{
}

InformationPanel::~InformationPanel()
{
}

void InformationPanel::setSelection(const KFileItemList& selection)
{
    m_selection = selection;
    m_fileItem = KFileItem();

    if (!isVisible()) {
        return;
    }

    const int count = selection.count();
    if (count == 0) {
        if (!isEqualToShownUrl(url())) {
            m_shownUrl = url();
            showItemInfo();
        }
    } else {
        if ((count == 1) && !selection.first().url().isEmpty()) {
            m_urlCandidate = selection.first().url();
        }
        m_infoTimer->start();
    }
}

void InformationPanel::requestDelayedItemInfo(const KFileItem& item)
{
    if (!isVisible() || (item.isNull() && m_fileItem.isNull())) {
        return;
    }

    if (QApplication::mouseButtons() & Qt::LeftButton) {
        // Ignore the request of an item information when a rubberband
        // selection is ongoing.
        return;
    }

    cancelRequest();

    if (item.isNull()) {
        // The cursor is above the viewport. If files are selected,
        // show information regarding the selection.
        if (!m_selection.isEmpty()) {
            m_fileItem = KFileItem();
            m_infoTimer->start();
        }
    } else if (item.url().isValid() && !isEqualToShownUrl(item.url())) {
        // The cursor is above an item that is not shown currently
        m_urlCandidate = item.url();
        m_fileItem = item;
        m_infoTimer->start();
    }
}

bool InformationPanel::urlChanged()
{
    if (!url().isValid()) {
        return false;
    }

    if (!isVisible()) {
        return true;
    }

    cancelRequest();
    m_selection.clear();

    if (!isEqualToShownUrl(url())) {
        m_shownUrl = url();
        m_fileItem = KFileItem();

        // Update the content with a delay. This gives
        // the directory lister the chance to show the content
        // before expensive operations are done to show
        // meta information.
        m_urlChangedTimer->start();
    }

    return true;
}

void InformationPanel::showEvent(QShowEvent* event)
{
    Panel::showEvent(event);
    if (!event->spontaneous()) {
        if (!m_initialized) {
            // do a delayed initialization so that no performance
            // penalty is given when Dolphin is started with a closed
            // Information Panel
            init();
        }

        m_shownUrl = url();
        showItemInfo();
    }
}

void InformationPanel::resizeEvent(QResizeEvent* event)
{
    if (isVisible()) {
        m_urlCandidate = m_shownUrl;
        m_infoTimer->start();
    }
    Panel::resizeEvent(event);
}

void InformationPanel::contextMenuEvent(QContextMenuEvent* event)
{
    showContextMenu(event->globalPos());
    Panel::contextMenuEvent(event);
}

void InformationPanel::showContextMenu(const QPoint &pos)
{
    QMenu popup(this);

    QAction* previewAction = popup.addAction(i18nc("@action:inmenu", "Preview"));
    previewAction->setIcon(QIcon::fromTheme(QStringLiteral("view-preview")));
    previewAction->setCheckable(true);
    previewAction->setChecked(InformationPanelSettings::previewsShown());

    QAction* previewAutoPlayAction = popup.addAction(i18nc("@action:inmenu", "Auto-Play media files"));
    previewAutoPlayAction->setIcon(QIcon::fromTheme(QStringLiteral("media-playback-start")));
    previewAutoPlayAction->setCheckable(true);
    previewAutoPlayAction->setChecked(InformationPanelSettings::previewsAutoPlay());

    QAction* configureAction = popup.addAction(i18nc("@action:inmenu", "Configure..."));
    configureAction->setIcon(QIcon::fromTheme(QStringLiteral("configure")));
    if (m_inConfigurationMode) {
        configureAction->setEnabled(false);
    }

    QAction* dateformatAction = popup.addAction(i18nc("@action:inmenu", "Condensed Date"));
    dateformatAction->setIcon(QIcon::fromTheme(QStringLiteral("change-date-symbolic")));
    dateformatAction->setCheckable(true);
    dateformatAction->setChecked(InformationPanelSettings::dateFormat() == static_cast<int>(Baloo::DateFormats::ShortFormat));

    popup.addSeparator();
    const auto actions = customContextMenuActions();
    for (QAction *action : actions) {
        popup.addAction(action);
    }

    // Open the popup and adjust the settings for the
    // selected action.
    QAction* action = popup.exec(pos);
    if (!action) {
        return;
    }

    const bool isChecked = action->isChecked();
    if (action == previewAction) {
        InformationPanelSettings::setPreviewsShown(isChecked);
        m_content->refreshPreview();
    } else if (action == configureAction) {
        m_inConfigurationMode = true;
        m_content->configureShownProperties();
    }
    if (action == dateformatAction) {
        int dateFormat = static_cast<int>(isChecked ? Baloo::DateFormats::ShortFormat : Baloo::DateFormats::LongFormat);

        InformationPanelSettings::setDateFormat(dateFormat);
        m_content->refreshMetaData();
    } else if (action == previewAutoPlayAction) {
        InformationPanelSettings::setPreviewsAutoPlay(isChecked);
        m_content->setPreviewAutoPlay(isChecked);
    }
}

void InformationPanel::showItemInfo()
{
    if (!isVisible()) {
        return;
    }

    cancelRequest();

    if (m_fileItem.isNull() && (m_selection.count() > 1)) {
        // The information for a selection of items should be shown
        m_content->showItems(m_selection);
    } else {
        // The information for exactly one item should be shown
        KFileItem item;
        if (!m_fileItem.isNull()) {
            item = m_fileItem;
        } else if (!m_selection.isEmpty()) {
            Q_ASSERT(m_selection.count() == 1);
            item = m_selection.first();
        }

        if (item.isNull()) {
            // No item is hovered and no selection has been done: provide
            // an item for the currently shown directory.
            m_folderStatJob = KIO::stat(url(), KIO::HideProgressInfo);
            if (m_folderStatJob->uiDelegate()) {
                KJobWidgets::setWindow(m_folderStatJob, this);
            }
            connect(m_folderStatJob, &KIO::Job::result,
                    this, &InformationPanel::slotFolderStatFinished);
        } else {
            m_content->showItem(item);
        }
    }
}

void InformationPanel::slotFolderStatFinished(KJob* job)
{
    m_folderStatJob = nullptr;
    const KIO::UDSEntry entry = static_cast<KIO::StatJob*>(job)->statResult();
    m_content->showItem(KFileItem(entry, m_shownUrl));
}

void InformationPanel::slotInfoTimeout()
{
    m_shownUrl = m_urlCandidate;
    m_urlCandidate.clear();
    showItemInfo();
}

void InformationPanel::reset()
{
    if (m_invalidUrlCandidate == m_shownUrl) {
        m_invalidUrlCandidate = QUrl();

        // The current URL is still invalid. Reset
        // the content to show the directory URL.
        m_selection.clear();
        m_shownUrl = url();
        m_fileItem = KFileItem();
        showItemInfo();
    }
}

void InformationPanel::slotFileRenamed(const QString& source, const QString& dest)
{
    if (m_shownUrl == QUrl::fromUserInput(source)) {
        m_shownUrl = QUrl::fromUserInput(dest);
        m_fileItem = KFileItem(m_shownUrl);

        if ((m_selection.count() == 1) && (m_selection[0].url() == QUrl::fromLocalFile(source))) {
            m_selection[0] = m_fileItem;
            // Implementation note: Updating the selection is only required if exactly one
            // item is selected, as the name of the item is shown. If this should change
            // in future: Before parsing the whole selection take care to test possible
            // performance bottlenecks when renaming several hundreds of files.
        }

        showItemInfo();
    }
}

void InformationPanel::slotFilesAdded(const QString& directory)
{
    if (m_shownUrl == QUrl::fromUserInput(directory)) {
        // If the 'trash' icon changes because the trash has been emptied or got filled,
        // the signal filesAdded("trash:/") will be emitted.
        KFileItem item(QUrl::fromUserInput(directory));
        requestDelayedItemInfo(item);
    }
}

void InformationPanel::slotFilesChanged(const QStringList& files)
{
    for (const QString& fileName : files) {
        if (m_shownUrl == QUrl::fromUserInput(fileName)) {
            showItemInfo();
            break;
        }
    }
}

void InformationPanel::slotFilesRemoved(const QStringList& files)
{
    for (const QString& fileName : files) {
        if (m_shownUrl == QUrl::fromUserInput(fileName)) {
            // the currently shown item has been removed, show
            // the parent directory as fallback
            markUrlAsInvalid();
            break;
        }
    }
}

void InformationPanel::slotEnteredDirectory(const QString& directory)
{
    if (m_shownUrl == QUrl::fromUserInput(directory)) {
        KFileItem item(QUrl::fromUserInput(directory));
        requestDelayedItemInfo(item);
    }
}

void InformationPanel::slotLeftDirectory(const QString& directory)
{
    if (m_shownUrl == QUrl::fromUserInput(directory)) {
        // The signal 'leftDirectory' is also emitted when a media
        // has been unmounted. In this case no directory change will be
        // done in Dolphin, but the Information Panel must be updated to
        // indicate an invalid directory.
        markUrlAsInvalid();
    }
}

void InformationPanel::cancelRequest()
{
    delete m_folderStatJob;
    m_folderStatJob = nullptr;

    m_infoTimer->stop();
    m_resetUrlTimer->stop();
    // Don't reset m_urlChangedTimer. As it is assured that the timeout of m_urlChangedTimer
    // has the smallest interval (see init()), it is not possible that the exceeded timer
    // would overwrite an information provided by a selection or hovering.

    m_invalidUrlCandidate.clear();
    m_urlCandidate.clear();
}

bool InformationPanel::isEqualToShownUrl(const QUrl& url) const
{
    return m_shownUrl.matches(url, QUrl::StripTrailingSlash);
}

void InformationPanel::markUrlAsInvalid()
{
    m_invalidUrlCandidate = m_shownUrl;
    m_resetUrlTimer->start();
}

void InformationPanel::init()
{
    m_infoTimer = new QTimer(this);
    m_infoTimer->setInterval(300);
    m_infoTimer->setSingleShot(true);
    connect(m_infoTimer, &QTimer::timeout,
            this, &InformationPanel::slotInfoTimeout);

    m_urlChangedTimer = new QTimer(this);
    m_urlChangedTimer->setInterval(200);
    m_urlChangedTimer->setSingleShot(true);
    connect(m_urlChangedTimer, &QTimer::timeout,
            this, &InformationPanel::showItemInfo);

    m_resetUrlTimer = new QTimer(this);
    m_resetUrlTimer->setInterval(1000);
    m_resetUrlTimer->setSingleShot(true);
    connect(m_resetUrlTimer, &QTimer::timeout,
            this, &InformationPanel::reset);

    Q_ASSERT(m_urlChangedTimer->interval() < m_infoTimer->interval());
    Q_ASSERT(m_urlChangedTimer->interval() < m_resetUrlTimer->interval());

    org::kde::KDirNotify* dirNotify = new org::kde::KDirNotify(QString(), QString(),
                                                               QDBusConnection::sessionBus(), this);
    connect(dirNotify, &OrgKdeKDirNotifyInterface::FileRenamed, this, &InformationPanel::slotFileRenamed);
    connect(dirNotify, &OrgKdeKDirNotifyInterface::FilesAdded, this, &InformationPanel::slotFilesAdded);
    connect(dirNotify, &OrgKdeKDirNotifyInterface::FilesChanged, this, &InformationPanel::slotFilesChanged);
    connect(dirNotify, &OrgKdeKDirNotifyInterface::FilesRemoved, this, &InformationPanel::slotFilesRemoved);
    connect(dirNotify, &OrgKdeKDirNotifyInterface::enteredDirectory, this, &InformationPanel::slotEnteredDirectory);
    connect(dirNotify, &OrgKdeKDirNotifyInterface::leftDirectory, this, &InformationPanel::slotLeftDirectory);

    m_content = new InformationPanelContent(this);
    connect(m_content, &InformationPanelContent::urlActivated, this, &InformationPanel::urlActivated);
    connect(m_content, &InformationPanelContent::configurationFinished, this, [this]() { m_inConfigurationMode = false; });

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(m_content);

    m_initialized = true;
}

