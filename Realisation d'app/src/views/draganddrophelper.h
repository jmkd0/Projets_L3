/***************************************************************************
 *   Copyright (C) 2007-2011 by Peter Penz <peter.penz19@gmail.com>        *
 *   Copyright (C) 2007 by David Faure <faure@kde.org>                     *
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

#ifndef DRAGANDDROPHELPER_H
#define DRAGANDDROPHELPER_H

#include "dolphin_export.h"

#include <QList>
#include <QUrl>

class QDropEvent;
class QWidget;
namespace KIO { class DropJob; }

class DOLPHIN_EXPORT DragAndDropHelper
{
public:
    /**
     * Handles the dropping of URLs to the given destination. A context menu
     * with the options 'Move Here', 'Copy Here', 'Link Here' and 'Cancel' is
     * offered to the user. The drag destination must represent a directory or
     * a desktop-file, otherwise the dropping gets ignored.
     *
     * @param destUrl   URL of the item destination. Is used only if destItem::isNull()
     *                  is true.
     * @param event     Drop event.
     * @param window    Widget where the drop happened, will be used as parent of the drop menu.
     * @return          KIO::DropJob pointer or null in case the destUrl is contained
     *                  in the mimeData url list.
     */
    static KIO::DropJob* dropUrls(const QUrl& destUrl,
                                  QDropEvent* event,
                                  QWidget *window);

    /**
     * @return True if destUrl is contained in the urls parameter.
     */
    static bool urlListMatchesUrl(const QList<QUrl>& urls, const QUrl& destUrl);

    /**
     * clear the internal cache.
     */
    static void clearUrlListMatchesUrlCache();
private:
    /**
     * Stores the results of the expensive checks made in urlListMatchesUrl.
     */
    static QHash<QUrl, bool> m_urlListMatchesUrlCache;
};

#endif
