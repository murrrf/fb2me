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

#ifndef TYPES_H
#define TYPES_H

/**
 * @file
 * @~russian
 * @brief Файл для размещения определений типов, используемых более чем в одном месте.
 *
 * @~english
 * @brief File to accommodate type definitions used in more than one place.
 */

#include <QString>
#include <QVector>
#include <QPair>

/**
 * @~russian
 * @brief Псевдоним типа для списка жанров книги.
 *
 * Первый параметр - наименование жанра.@n
 * Второй параметр - совпадение с жанром в процентах:@n
 * 100 - полное совпадение с жанром.
 *
 * @~english
 * @brief Type definition for genres list of the book.
 *
 * First parameter - name of the genre.@n
 * Second parameter - the match with the genre as a percentage:@n
 * 100 - full match.
 */
typedef QVector<QPair<QString, int> > genre_t;

/**
 * @~russian
 * @brief Псевдоним типа для списка серий книги.
 *
 * Первый параметр - наименование серии.@n
 * Второй параметр - номер произведения в серии.
 *
 * @~english
 * @brief Type definition for series list of the book.
 *
 * First parameter - name of the sequence.@n
 * Second parameter - book number in the sequence.
 */
typedef QVector<QPair<QString, int> > sequence_t;

/**
 * @~russian
 * @brief Псевдоним типа для списка настроек.
 *
 * Первый параметр - имя ключа (отображаемое значение).@n
 * Второй параметр - значение ключа (применяемое значение).
 *
 * @~english
 * @brief Type definition for settings list.
 *
 * First parameter - key name (displayed value).@n
 * Second parameter - key value (used value).
 */
typedef QVector<QPair<QString, QString> > setting_t;

#endif // TYPES_H
