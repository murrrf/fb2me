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
     * @~russian
     * @brief Конструктор потока чтения.
     * @param files Список файлов для чтения.
     *
     * @~english
     * @brief Constructor of reading thread.
     * @param files List of file names for reading.
     */
    Reader(QStringList files);

    /**
     * @~russian
     * @brief Конструктор потока чтения.
     * @param dir Папка, в которой будут считываться файлы.
     * @param recursive Обрабатывать ли подпапки:@n
     * @c true - да;@n
     * @c false - нет.
     *
     * @~english
     * @brief Constructor of reading thread.
     * @param dir The folder in which files will be read.
     * @param recursive Read folder recursively:@n
     * @c true - yes;@n
     * @ false - no.
     */
    Reader(QString dir, bool recursive);

    /**
     * @~russian
     * @brief Тело потока вычисления.
     *
     * @~english
     * @brief Body of the thread.
     */
    void run();

signals:

public slots:
    /**
     * @~russian
     * @brief Список имен файлов.
     * 
     * @~english
     * @brief List of file names.
     */
    QStringList filenames;

};

#endif // READER_H