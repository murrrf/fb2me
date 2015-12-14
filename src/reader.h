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

#include "fb2record.h"

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
    /**
     * @~russian
     * @brief Отсылка сообщения в журнал сообщений.
     * @param msg Текст сообщения.
     *
     * @~english
     * @brief Sending messages to the message log.
     * @param msg Message text.
     */
    void EventMessage(const QString &msg);

    /**
     * @~russian
     * @brief Добавление новой записи в модель данных.
     * @param record Добавляемая запись.
     *
     * @~english
     * @brief Append new record to data model.
     * @param record Appended record.
     */
    void AppendRecord(const FB2Record &record);

public slots:

private:
    /**
     * @~russian
     * @brief Список имен файлов.
     *
     * @~english
     * @brief List of file names.
     */
    QStringList filenames;

    /**
     * @~russian
     * @brief Проверка, является ли файл архивом.
     *
     * В настоящее время проверка осуществляется простым тестом расширения файла.@n
     * Возможно, в будущем будет применен более точный алгоритм проверки.
     * @param filename Имя файла.
     * @return @c true - если файл - архив;@n
     * @c false - обычный файл.
     *
     * @~english
     * @brief Check whether a file is archive.
     *
     * Currently, check with a simple test file extension.@n
     * Perhaps in the future will be used more detailed checking algorithm.
     * @param filename File name.
     * @return @c true - if file is archive;@n
     * @c false - if not.
     */
    bool isFileArchive(const QString &filename);

    /**
     * @~russian
     * @brief Разбор файла и заполнение полей записи значениями, полученными из файла.
     * @param data Файл в виде потока байтов.
     * @param record Запись, в которой сохраняются значения.
     *
     * @~english
     * @brief Parsing the file and populates the fields recording the values obtained from the file.
     * @param data File as byte array.
     * @param record Record, in which are stored values.
     */
    void parseFile(QByteArray &data, FB2Record &record);

};

#endif // READER_H
