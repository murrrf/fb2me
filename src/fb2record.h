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

#ifndef FB2RECORD_H
#define FB2RECORD_H

/**
 * @file
 * @~russian
 * @brief Модуль единичной записи метаданных.
 *
 * @~english
 * @brief Module of single metadata record.
 */

#include <QString>
#include <QVector>

// Forward declarations
class Person;

/**
 * @~russian
 * @brief Перечисление возможных статусов записи.
 *
 * @~english
 * @brief Enumeration of statuses of the record.
 */
enum Status
{
    stNormalRecord, ///< @~russian Нормальная запись. @~english Normal record.
    stIncorrectAuthorField, ///< @~russian Поле «Автор» не соответствует стандарту. @~english Non-standard «Author» field.
    stMixedCyrLat ///< @~russian В строке, составленной из имени автора и названия книги, смешаны кириллица и латиница. @~english Mixed cyrillic and latin symbols in author and title.
};

/**
 * @~russian
 * @brief Класс единичной записи метаданных.
 *
 * @~english
 * @brief Single metadata record class.
 */
class FB2Record
{
public:
    /**
     * @~russian
     * @brief Конструктор записи.
     *
     * @~english
     * @brief Constructor of a record.
     */
    FB2Record();

    /*
     * @~russian
     * @brief Деструктор записи.
     *
     * @~english
     * @brief Destructor of a record.
     */
//    ~FB2Record();

private:
    /*
     * @~russian
     * @brief
     *
     * @~english
     * @brief
     */
    /**
     * @~russian
     * @brief Состояние записи - для различных отображений.
     *
     * @~english
     * @brief Status of the record.
     */
    Status status;

    /**
     * @~russian
     * @brief Название книги.
     *
     * Один, обязательно.
     *
     * @~english
     * @brief Book title.
     *
     * One, required.
     */
    QString BookTitle;

    /**
     * @~russian
     * @brief Автор книги.
     *
     * Один или более, обязательно.
     *
     * @~english
     * @brief Book author.
     *
     * One or more, required.
     */
    QVector<Person> BookAuthor;

};


#endif // FB2RECORD_H
