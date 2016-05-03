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
class QGroupBox;
class QVBoxLayout;
class QHBoxLayout;
class QTableWidget;
class QPushButton;

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
     * @param title Заголовок виджета.
     * @param parent Указатель на родительское окно.
     *
     * @~english
     * @brief Class constructor.
     * @param title Widget caption.
     * @param parent Parent window pointer.
     */
    explicit SettingsHelper(const QString &title, QWidget *parent = 0);

    /**
     * @~russian
     * @brief Деструктор класса.
     *
     * @~english
     * @brief Class destructor.
     */
    virtual ~SettingsHelper();

    /**
     * @~russian
     * @brief SetHelp
     * @param help
     *
     * @~english
     * @brief SetHelp
     * @param help
     */
    void SetHelp(const QString &help);

private:

    /**
     * @~russian
     * @brief Главный менеджер размещения элементов.
     *
     * @~english
     * @brief Main layout manager.
     */
    QVBoxLayout *boxMain;

    /**
     * @~russian
     * @brief Таблица данных настроек.
     *
     * @~english
     * @brief Table of settings data.
     */
    QTableWidget *tblData;

signals:

    /**
     * @~russian
     * @brief Сигнал «Передвинуть вверх».
     *
     * @~english
     * @brief «Move up» signal.
     */
    void Add();

    /**
     * @~russian
     * @brief Сигнал «Передвинуть вниз».
     *
     * @~english
     * @brief «Move down» signal.
     */
    void Edit();

    /**
     * @~russian
     * @brief Сигнал «Удалить».
     *
     * @~english
     * @brief «Delete» signal.
     */
    void Delete();

};

#endif // SETTINGSHELPER_H
