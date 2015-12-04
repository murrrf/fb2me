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

#ifndef READER_H
#define READER_H

/**
 * @file
 * @~russian
 * @brief Модуль чтения файлов.
 *
 * Чтение осуществляется в отдельном потоке.
 *
 * @~english
 * @brief Module of file reading.
 *
 * Reading is performed in a separate thread.
 */

#include <QThread>
#include <QString>
#include <QStringList>

/**
 * @~russian
 * @brief Поток чтения файлов.
 *
 * @~english
 * @brief Thread of file reading.
 */
class Reader : public QThread
{
    Q_OBJECT
public:
    /**
     * @~
     * @brief Reader
     * @param files
     *
     * @~
     * @brief Reader
     * @param files
     */
    Reader(QStringList files);

    /**
     * @~
     * @brief Reader
     * @param dir
     * @param recursive
     *
     * @~
     * @brief Reader
     * @param dir
     * @param recursive
     */
    Reader(QString dir, bool recursive);

    void run();

    void stop();

signals:

public slots:

};

#endif // READER_H
