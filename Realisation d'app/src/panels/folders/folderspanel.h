/***************************************************************************
 *   Copyright (C) 2006 by Peter Penz <peter.penz19@gmail.com>             *
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

#ifndef FOLDERSPANEL_H
#define FOLDERSPANEL_H

#include "panels/panel.h"

#include <QUrl>

class KFileItemModel;
class KItemListController;
class QGraphicsSceneDragDropEvent;
class KFileItem;
/**
 * @brief Shows a tree view of the directories starting from
 *        the currently selected place.
 *
 * The tree view is always synchronized with the currently active view
 * from the main window.
 */
class FoldersPanel : public Panel
{
    Q_OBJECT

public:
    explicit FoldersPanel(QWidget* parent = nullptr);
    ~FoldersPanel() override;

    void setShowHiddenFiles(bool show);
    void setLimitFoldersPanelToHome(bool enable);
    bool showHiddenFiles() const;
    bool limitFoldersPanelToHome() const;

    void setAutoScrolling(bool enable);
    bool autoScrolling() const;

    void rename(const KFileItem& item);

signals:
    void folderActivated(const QUrl& url);
    void folderMiddleClicked(const QUrl& url);
    void errorMessage(const QString& error);

protected:
    /** @see Panel::urlChanged() */
    bool urlChanged() override;

    /** @see QWidget::showEvent() */
    void showEvent(QShowEvent* event) override;

    /** @see QWidget::keyPressEvent() */
    void keyPressEvent(QKeyEvent* event) override;

private slots:
    void slotItemActivated(int index);
    void slotItemMiddleClicked(int index);
    void slotItemContextMenuRequested(int index, const QPointF& pos);
    void slotViewContextMenuRequested(const QPointF& pos);
    void slotItemDropEvent(int index, QGraphicsSceneDragDropEvent* event);
    void slotRoleEditingFinished(int index, const QByteArray& role, const QVariant& value);

    void slotLoadingCompleted();

    /**
     * Increases the opacity of the view step by step until it is fully
     * opaque.
     */
    void startFadeInAnimation();


private:
    /**
     * Indicate if it is allowed to leave current location.
     */
    enum NavigationBehaviour {
      StayWhereYouAre,  ///< Don't leave current location.
      AllowJumpHome     ///< Go Home only when context menu option got checked.
    };
    /**
     * Initializes the base URL of the tree and expands all
     * directories until \a url.
     * @param url  URL of the leaf directory that should get expanded.
     * @param navigationBehaviour Navigation behaviour \see NavigationBehaviour
     */
    void loadTree(const QUrl& url, NavigationBehaviour navigationBehaviour = StayWhereYouAre);

    void reloadTree();

    /**
     * Sets the item with the index \a index as current item, selects
     * the item and assures that the item will be visible.
     */
    void updateCurrentItem(int index);

private:
    bool m_updateCurrentItem;
    KItemListController* m_controller;
    KFileItemModel* m_model;
};

#endif // FOLDERSPANEL_H
