/***************************************************************************
 *   Copyright (C) 2011 by Peter Penz <peter.penz19@gmail.com>             *
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
 *   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA          *
 ***************************************************************************/

#ifndef CONFIGUREPREVIEWPLUGINDIALOG_H
#define CONFIGUREPREVIEWPLUGINDIALOG_H

#include <QDialog>

/**
 * @brief Dialog for configuring preview-plugins.
 */
class ConfigurePreviewPluginDialog : public QDialog
{
    Q_OBJECT

public:
    /**
     * @param pluginName       User visible name of the plugin
     * @param desktopEntryName The name of the plugin that is noted in the desktopentry.
     *                         Is used to instantiate the plugin to get the configuration
     *                         widget.
     * @param parent           Parent widget.
     */
    ConfigurePreviewPluginDialog(const QString& pluginName,
                                 const QString& desktopEntryName,
                                 QWidget* parent);
    ~ConfigurePreviewPluginDialog() override = default;
};

#endif
