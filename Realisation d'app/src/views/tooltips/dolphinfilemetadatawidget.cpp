/***************************************************************************
 *   Copyright (C) 2010 by Peter Penz <peter.penz19@gmail.com>             *
 *   Copyright (C) 2008 by Fredrik Höglund <fredrik@kde.org>               *
 *   Copyright (C) 2012 by Mark Gaiser <markg85@gmail.com>                 *
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

#include "dolphinfilemetadatawidget.h"

#include <KColorScheme>
#include <KSeparator>
#include <KStringHandler>
#include <Baloo/FileMetaDataWidget>

#include <QLabel>
#include <QStyleOptionFrame>
#include <QStylePainter>
#include <QTextDocument>
#include <QTextLayout>
#include <QVBoxLayout>

DolphinFileMetaDataWidget::DolphinFileMetaDataWidget(QWidget* parent) :
    QWidget(parent),
    m_preview(nullptr),
    m_name(nullptr),
    m_fileMetaDataWidget(nullptr)
{
    // Create widget for file preview
    m_preview = new QLabel(this);
    m_preview->setAlignment(Qt::AlignTop);

    // Create widget for file name
    m_name = new QLabel(this);
    m_name->setForegroundRole(QPalette::ToolTipText);
    m_name->setTextFormat(Qt::PlainText);
    m_name->setAlignment(Qt::AlignHCenter);

    QFont font = m_name->font();
    font.setBold(true);
    m_name->setFont(font);

    QFontMetrics fontMetrics(font);
    m_name->setMaximumWidth(fontMetrics.averageCharWidth() * 40);

    // Create widget for the meta data
    m_fileMetaDataWidget = new Baloo::FileMetaDataWidget(this);
    connect(m_fileMetaDataWidget, &Baloo::FileMetaDataWidget::metaDataRequestFinished,
            this, &DolphinFileMetaDataWidget::metaDataRequestFinished);
    connect(m_fileMetaDataWidget, &Baloo::FileMetaDataWidget::urlActivated,
            this, &DolphinFileMetaDataWidget::urlActivated);
    m_fileMetaDataWidget->setForegroundRole(QPalette::ToolTipText);
    m_fileMetaDataWidget->setReadOnly(true);

    QVBoxLayout* textLayout = new QVBoxLayout();
    textLayout->addWidget(m_name);
    textLayout->addWidget(new KSeparator());
    textLayout->addWidget(m_fileMetaDataWidget);
    textLayout->setAlignment(m_name, Qt::AlignCenter);
    textLayout->setAlignment(m_fileMetaDataWidget, Qt::AlignLeft);
    // Assure that the text-layout gets top-aligned by adding a stretch.
    // Don't use textLayout->setAlignment(Qt::AlignTop) instead, as this does
    // not work with the heightForWidth()-size-hint of m_fileMetaDataWidget
    // (see bug #241608)
    textLayout->addStretch();

    QHBoxLayout* layout = new QHBoxLayout(this);
    layout->addWidget(m_preview);
    layout->addSpacing(layout->margin());
    layout->addLayout(textLayout);
}

DolphinFileMetaDataWidget::~DolphinFileMetaDataWidget()
{
}

void DolphinFileMetaDataWidget::setPreview(const QPixmap& pixmap)
{
    m_preview->setPixmap(pixmap);
}

QPixmap DolphinFileMetaDataWidget::preview() const
{
    if (m_preview->pixmap()) {
        return *m_preview->pixmap();
    }
    return QPixmap();
}

void DolphinFileMetaDataWidget::setName(const QString& name)
{
    QTextOption textOption;
    textOption.setWrapMode(QTextOption::WrapAtWordBoundaryOrAnywhere);

    const QString processedName = Qt::mightBeRichText(name) ? name : KStringHandler::preProcessWrap(name);

    QTextLayout textLayout(processedName);
    textLayout.setFont(m_name->font());
    textLayout.setTextOption(textOption);

    QString wrappedText;
    wrappedText.reserve(processedName.length());

    // wrap the text to fit into the maximum width of m_name
    textLayout.beginLayout();
    QTextLine line = textLayout.createLine();
    while (line.isValid()) {
        line.setLineWidth(m_name->maximumWidth());
        wrappedText += processedName.midRef(line.textStart(), line.textLength());

        line = textLayout.createLine();
        if (line.isValid()) {
            wrappedText += QChar::LineSeparator;
        }
    }
    textLayout.endLayout();

    m_name->setText(wrappedText);
}

QString DolphinFileMetaDataWidget::name() const
{
    return m_name->text();
}

void DolphinFileMetaDataWidget::setItems(const KFileItemList& items)
{
    m_fileMetaDataWidget->setItems(items);
}

KFileItemList DolphinFileMetaDataWidget::items() const
{
    return m_fileMetaDataWidget->items();
}

