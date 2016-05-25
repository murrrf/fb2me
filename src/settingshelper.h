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

#include "types.h"

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
class SettingsHelper : public QWidget
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
     * @brief Установка заголовков столбцов таблицы.
     * @param key Заголовок столбца "Ключ".
     * @param value Заголовок столбца "Значение".
     *
     * @~english
     * @brief Setting of the column headers of the table.
     * @param key The column heading "Key".
     * @param value The column heading "Value".
     */
    void setColumnHeaders(const QString &key, const QString &value);

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

    /**
     * @~russian
     * @brief Получение списка пар ключ-значение, сформированных в виджете.
     * @return Список пар ключ-значение.
     *
     * @~english
     * @brief Getting a list of key-value pairs formed in the widget.
     * @return List of key-value pairs.
     */
    setting_t getSettingsList();

    /**
     * @~russian
     * @brief Внесение в виджет списка пар ключ-значение.
     * @param list Список пар ключ-значение.
     *
     * @~english
     * @brief Adding to the widget list of key-value pairs.
     * @param list List of key-value pairs.
     */
    void setSettingsList(setting_t list);

public slots:

    /**
     * @~russian
     * @brief Обработчик кнопки «Добавление нового значения».
     *
     * @~english
     * @brief Handler clicking the «Add a new settings value» button.
     */
    void onAdd();

    /**
     * @~russian
     * @brief Обработчик кнопки «Редактирование существующего значения».
     *
     * @~english
     * @brief Handler clicking the «Edit the existing value» button.
     */
    void onEdit();

    /**
     * @~russian
     * @brief Обработчик кнопки «Удаление существующего значения».
     *
     * @~english
     * @brief Handler clicking the «Delete the existing value» button.
     */
    void onDelete();

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

};


#endif // SETTINGSHELPER_H
