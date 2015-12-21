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

#ifndef FILERECORD_H
#define FILERECORD_H

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
#include <QPair>

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
 * @brief Класс единичной записи метаданных.
 *
 * @~english
 * @brief Single metadata record class.
 */
class FileRecord
{
public:
    /**
     * @~russian
     * @brief Конструктор записи.
     *
     * @~english
     * @brief Constructor of a record.
     */
    FileRecord();

    /*
     * @~russian
     * @brief Деструктор записи.
     *
     * @~english
     * @brief Destructor of a record.
     */
//    ~FileRecord();

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

    /**
     * @~russian
     * @brief Добавление жанра в список жанров.
     * @param genre_name Наименование жанра.
     * @param genre_match Совпадение с жанром в процентах.
     *
     * Если не указано, то 100% (полное совпадение).
     *
     * @~english
     * @brief Adding genre to the list of genres.
     * @param genre_name Name of the genre.
     * @param genre_match The coincidence with the genre as a percentage.
     *
     * If not specified, the 100% (complete agreement).
     */
    void addGenre(QString genre_name, int genre_match = 100);

    /**
     * @~russian
     * @brief Получение списка жанров файла.
     *
     * Для дальнейшего форматирования список выдается «как есть».
     * @return Список жанров.
     *
     * @~english
     * @brief Getting the list of genres of the file.
     *
     * For a further formatting list  issued "as is".
     * @return List of genres.
     */
    genre_t getGenresList();

    /**
     * @~russian
     * @brief Установка кодировки файла.
     * @param Encoding Кодировка.
     *
     * @~english
     * @brief Setting of file encoding.
     * @param Encoding Encoding
     */
    void setEncoding(QString Encoding);

    /**
     * @~russian
     * @brief Получение кодировки файла.
     * @return Кодировка.
     *
     * @~english
     * @brief Getting of file encoding.
     * @return Encoding
     */
    QString getEncoding() const;

    /**
     * @~russian
     * @brief Добавление нового автора в список авторов записи.
     * @param author Добавляемый автор.
     *
     * @~english
     * @brief Adding a new author in the list of authors of the record.
     * @param author Author.
     */
    void addAuthor(Person author);

    /**
     * @~russian
     * @brief Получение списка авторов.
     *
     * Список выдается в формате "Фамилия Имя Отчество", каждый автор на отдельной строке.
     * @return Список авторов.
     *
     * @~english
     * @brief Getting a list of authors.
     *
     * List issued in the format of "Full Name", every author on a separate line.
     * @return List of authors.
     */
    QStringList getAuthorList();

    /**
     * @~russian
     * @brief Добавление серии в список серий.
     * @param sequence Наименование серии.
     * @param number Номер произведения в серии.
     *
     * Если не указано, то 0 (ненумерованое произведение серии).
     *
     * @~english
     * @brief Adding new sequence to the list of series.
     * @param sequence Name of the sequence.
     * @param number Book number in the sequence.
     *
     * If not specified, 0 (unnumbered book in the series).
     */
    void addSequence(QString sequence, int number = 0);

    /**
     * @~russian
     * @brief Получение списка серий файла.
     *
     * Для дальнейшего форматирования список выдается «как есть».
     * @return Список серий.
     *
     * @~english
     * @brief Getting the list of series of the file.
     *
     * For a further formatting list  issued "as is".
     * @return List of series.
     */
    sequence_t getSequenceList();

    /**
     * @~russian
     * @brief Установка и снятие пометки «Запись выбрана».
     * @param Selected Статус записи:
     * @c true - запись помечена как выбранная;@n
     * @c false - запись помечена как невыбранная.
     *
     * @~english
     * @brief Set and unset record as selected.
     * @param Selected Status of entry:
     * @c true - a record marked as selected;@n
     * @c false - a record marked as unselected.
     */
    void setSelected(bool Selected);

    /**
     * @~russian
     * @brief Получение пометки, выбрана ли запись.
     * @return Статус записи:
     * @c true - запись помечена как выбранная;@n
     * @c false - запись помечена как невыбранная.
     *
     * @~english
     * @brief Getting state whether the record is selected.
     * @return Status of entry:
     * @c true - a record marked as selected;@n
     * @c false - a record marked as unselected.
     */
    bool isSelected();

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

    /**
     * @~russian
     * @brief Список жанров файла.
     *
     * @~english
     * @brief Genres list of the file.
     */
    genre_t Genres;

    /**
     * @~russian
     * @brief Список серий файла.
     *
     * @~english
     * @brief Series list of the file.
     */
    sequence_t Sequences;

    /**
     * @~russian
     * @brief Кодировка файла.
     *
     * @~english
     * @brief Encoding of the file.
     */
    QString encoding;

    /**
     * @~russian
     * @brief Состояние пометки записи.
     *
     * @~english
     * @brief The status of record selection.
     */
    bool selected;

};

#endif // FILERECORD_H
