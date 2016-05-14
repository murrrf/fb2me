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
 * @~english
 * @brief Type definition for genres list of the book.
 */
typedef QVector<QPair<QString, int> > genre_t;

/**
 * @~russian
 * @brief Псевдоним типа для списка серий книги.
 *
 * @~english
 * @brief Type definition for series list of the book.
 */
typedef QVector<QPair<QString, int> > sequence_t;

/**
 * @~russian
 * @brief Псевдоним типа для списка настроек.
 *
 * @~english
 * @brief Type definition for settings list.
 */
typedef QVector<QPair<QString, QString> > setting_t;

#endif // TYPES_H
