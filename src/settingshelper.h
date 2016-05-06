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
     * @brief Установка текста подсказки в виджете настроек.
     * @param help Текст подсказки.
     *
     * @~english
     * @brief Setting the help text in the settings widget.
     * @param help Help text.
     */
    void setHelpString(const QString &help);

    /**
     * @~russian
     * @brief Получение номера строки, в которой расположен выбранный элемент.
     * @return Номер строки.
     *
     * @~english
     * @brief Returns the row of the current item.
     * @return Row number.
     */
    int currentRow();

    /**
     * @~russian
     * @brief Добавление нового элемента в конец таблицы.
     * @param key Текст первого столбца таблицы - ключ элемента.
     * @param value Текст второго столбца таблицы - значение элемента.
     *
     * @~english
     * @brief Adding new item in the end of table.
     * @param key Text of first column - key of item.
     * @param value Text of second column - value of item.
     */
    void addItem(const QString &key, const QString &value);

    /**
     * @~russian
     * @brief Редактирование элемента таблицы.
     * @param row Номер строки, в которой расположен редактируемый элемент.
     * @param key Текст первого столбца таблицы - ключ элемента.
     * @param value Текст второго столбца таблицы - значение элемента.
     *
     * @~english
     * @brief Editing of table item.
     * @param row Row number.
     * @param key Text of first column - key of item.
     * @param value Text of second column - value of item.
     */
    void editItem(const int row, const QString &key, const QString &value);

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
