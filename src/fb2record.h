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

#include "person.h"

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

// TODO Move columns enumeration to data model file

/**
 * @~russian
 * @brief Перечисление полей записи.
 *
 * @~english
 * @brief Enumeration of fields of the record.
 */
enum Columns
{
    colCheckColumn, ///< @~russian Псевдополе - столбец с флажком. @~english Pseudofield - column with checkbox.
    colBookTitle, ///< @~russian Поле «Название книги». @~english Book title field.
    colBookAuthor, ///< @~russian Поле «Автор(ы) книги». @~english List of book authors field.
    colSeries, ///< @~russian Поле «Серия». @~english Series field.
    colGenres, ///< @~russian Поле «Жанр». @~english Genres field.
    colEncoding, ///< @~russian Поле «Кодировка». @~english Encoding field.
    colIsArchive, ///< @~russian Поле «Сжатый файл». @~english Is File Compressed field.
    colFileSize, ///< @~russian Поле «Размер файла». @~english File size field.
    colCounterField ///< @~russian Псевдополе - маркер конца перечисления. @warning Не использовать его иным образом! @~english Pseudofield - end marker listing. @warning Do not use it otherwise!
};

// TODO Move columns names to data model HeaderData() function

static const char T_BOOKTITLE[] = QT_TRANSLATE_NOOP_UTF8("TableModel", "Book title");
static const char T_BOOKAUTHOR[] = QT_TRANSLATE_NOOP_UTF8("TableModel", "Book author");
static const char T_SERIES[] = QT_TRANSLATE_NOOP_UTF8("TableModel", "Series");
static const char T_GENRES[] = QT_TRANSLATE_NOOP_UTF8("TableModel", "Genres");
static const char T_ENCODING[] = QT_TRANSLATE_NOOP_UTF8("TableModel", "Encoding");
static const char T_ISARCHIVE[] = QT_TRANSLATE_NOOP_UTF8("TableModel", "Archived");
static const char T_FILESIZE[] =  QT_TRANSLATE_NOOP_UTF8("TableModel", "File size");

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

    /**
     * @~russian
     * @brief Установка размера файла.
     * @param Size Размер файла.
     *
     * @~english
     * @brief Setting of file size.
     * @param Size File size.
     */
    void setSize(qint64 Size);

    /**
     * @~russian
     * @brief Получение размера файла.
     * @return Размер файла.
     *
     * @~english
     * @brief Getting of file size.
     * @return File size.
     */
    qint64 getSize();

    /**
     * @~russian
     * @brief Установка имени файла.
     * @param Filename Имя файла.
     *
     * @~english
     * @brief Setting of file name.
     * @param Filename File name.
     */
    void setFileName(const QString &Filename);

    /**
     * @~russian
     * @brief Получение имени файла.
     * @return Имя файла.
     *
     * @~english
     * @brief Getting of file name.
     * @return File name.
     */
    QString getFileName() const;

    /**
     * @~russian
     * @brief Установка флага «Файл-архив».
     *
     * @c true - если файл - архив;@n
     * @c false - обычный файл.
     * @param IsArchive Устанавливаемое значение.
     *
     * @~english
     * @brief Setting the flag "archive file."
     *
     * @c true - if file is archive;@n
     * @c false - if not.
     * @param IsArchive Setting value.
     */
    void setIsArchive(bool IsArchive);

    /**
     * @~russian
     * @brief Получение значения флага «Файл-архив».
     * @return @c true - если файл - архив;@n
     * @c false - обычный файл.
     *
     * @~english
     * @brief Getting the flag "archive file."
     * @return @c true - if file is archive;@n
     * @c false - if not.
     */
    bool isArchive();

    /**
     * @~russian
     * @brief Установка названия книги.
     * @param title Название книги
     *
     * @~english
     * @brief Setting of book title.
     * @param title Book title.
     */
    void setBookTitle(QString title);

    /**
     * @~russian
     * @brief Получение названия книги.
     * @return Название книги.
     *
     * @~english
     * @brief Getting of book title.
     * @return Book title.
     */
    QString getBookTitle();

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
     * @brief Полное имя файла.
     *
     * @~english
     * @brief Full file name.
     */
    QString filename;

    /**
     * @~russian
     * @brief Размер файла.
     *
     * @~english
     * @brief File size.
     */
    qint64 size;

    /**
     * @~russian
     * @brief Является ли файл архивом.
     *
     * @c true - если файл - архив;@n
     * @c false - обычный файл.
     *
     * @~english
     * @brief Is a file archive?
     *
     * @c true - if file is archive;@n
     * @c false - if not.
     */
    bool archived;

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
