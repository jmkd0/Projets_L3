/*
 * Copyright 2015 Ashish Bansal<bansal.ashish096@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the
 * Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

#ifndef GLOBAL_H
#define GLOBAL_H

#include <QList>
#include <QUrl>
#include <QWidget>

namespace Dolphin {
    QList<QUrl> validateUris(const QStringList& uriList);

    /**
     * Returns the home url which is defined in General Settings
     */
    QUrl homeUrl();

    enum class OpenNewWindowFlag {
        None = 0,
        Select = 1<<1
    };
    Q_DECLARE_FLAGS(OpenNewWindowFlags, OpenNewWindowFlag)

    /**
     * Opens a new Dolphin window
     */
    void openNewWindow(const QList<QUrl> &urls = {}, QWidget *window = nullptr, const OpenNewWindowFlags &flags = OpenNewWindowFlag::None);

    /**
     * Attaches URLs to an existing Dolphin instance if possible.
     * If @p preferredService is a valid dbus service, it will be tried first.
     * @p preferredService needs to support the org.kde.dolphin.MainWindow dbus interface with the /dolphin/Dolphin_1 path.
     * Returns true if the URLs were successfully attached.
     */
    bool attachToExistingInstance(const QList<QUrl>& inputUrls, bool openFiles, bool splitView, const QString& preferredService = QString());

    /**
     * TODO: Move this somewhere global to all KDE apps, not just Dolphin
     */
    const int VERTICAL_SPACER_HEIGHT = 18;
    const int LAYOUT_SPACING_SMALL = 2;
}

#endif //GLOBAL_H
