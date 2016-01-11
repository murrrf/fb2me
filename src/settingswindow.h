/***********************************************************************
 *
 * Copyright (C) 2015 Veter <veter@veter.name>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 ***********************************************************************/

#ifndef SETTINGSWINDOW_H
#define SETTINGSWINDOW_H

/**
 * @file
 * @~russian
 * @brief Модуль окна настроек.
 *
 * @~english
 * @brief The module of the settings window.
 */

#include <QDialog>

// Forward class declarations
class QVBoxLayout;
class QDialogButtonBox;
class QPushButton;

/**
 * @~russian
 * @brief Класс окна настроек.
 *
 * @~english
 * @brief The SettingsWindow class.
 */
class SettingsWindow : public QDialog
{
    Q_OBJECT
public:
    /**
     * @~russian
     * @brief Конструктор окна настроек.
     * @param parent Указатель на родительское окно.
     *
     * @~english
     * @brief The settings window constructor.
     * @param parent Parent window pointer.
     */
    SettingsWindow(QWidget *parent = 0);

private:

    /**
     * @~russian
     * @brief Менеджер размещения элементов диалога.
     *
     * @~english
     * @brief Layout manager for dialog.
     */
    QVBoxLayout *boxMain;

    /**
     * @~russian
     * @brief Менеджер размещения кнопок управления диалогом.
     *
     * @~english
     * @brief Layout manager for dialog buttons.
     */
    QDialogButtonBox *boxButtons;
};

#endif // SETTINGSWINDOW_H