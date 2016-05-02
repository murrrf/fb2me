/***********************************************************************
 *
 * Copyright (C) 2016 Sergej Martynov <veter@veter.name>
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

#ifndef SETTINGSHELPER_H
#define SETTINGSHELPER_H

/**
 * @file
 * @~russian
 * @brief Модуль виджета окна настроек.
 *
 * @~english
 * @brief The module of the settings widget.
 */

#include <QGroupBox>
#include <QWidget>

// Forward class declarations
class QVBoxLayout;
class QHBoxLayout;
class QPushButton;
class QGroupBox;

/**
 * @~russian
 * @brief Базовый класс вспомогательных классов, использующихся в окне настроек.
 *
 * @~english
 * @brief Base class of helper classes used in the settings window.
 */
class SettingsHelper : public QGroupBox
{
    Q_OBJECT
public:
    /**
     * @~russian
     * @brief Конструктор класса.
     * @param parent Указатель на родительское окно.
     *
     * @~english
     * @brief Class constructor.
     * @param parent Parent window pointer.
     */
    explicit SettingsHelper(QWidget *parent = 0);

    /**
     * @~russian
     * @brief Деструктор класса.
     *
     * @~english
     * @brief Class destructor.
     */
    virtual ~SettingsHelper();
};

#endif // SETTINGSHELPER_H
