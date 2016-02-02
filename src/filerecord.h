/***********************************************************************
 *
 * Copyright (C) 2015,2016 Sergej Martynov <veter@veter.name>
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
    bool isArchive() const;

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
    QString getBookTitle() const;

    /**
     * @~russian
     * @brief Получение названия книги вместе с расширением файла.
     * @return Полное название книги.
     *
     * @~english
     * @brief Getting the title of the book, along with the file extension.
     * @return Full book title.
     */
    QString getBookTitleExt() const;

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
     * @brief Получение автора из списка авторов.
     * @param index Позиция автора в списке.
     * @return Запись об авторе.
     *
     * @~english
     * @brief Getting the author from the list of authors.
     * @param index Author's position in the list.
     * @return Author's record.
     */
    Person getAuthor(int index) const;

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
    sequence_t getSequenceList() const;

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

    /**
     * @~russian
     * @brief Распаковка содержимого указанного архива.
     * @return Сообщение о результате операции.
     *
     * @~english
     * @brief Unpack the contents of the specified file.
     * @return Message result.
     */
    QString unzipFile();

    /**
     * @~russian
     * @brief Упаковка указанного файла в архив.
     * @return Сообщение о результате операции.
     *
     * @~english
     * @brief Packing the specified file to the archive.
     * @return Message result.
     */
    QString zipFile();

    /**
     * @~russian
     * @brief Перемещение указанного файла.
     * @param newName Имя файла после перемещения.
     * @return Сообщение о результате операции.
     *
     * @~english
     * @brief Moving of the specified file.
     * @param newName File name after moving.
     * @return Message result.
     */
    QString moveFile(QString newName);

    /**
     * @~russian
     * @brief Копирование указанного файла.
     * @param newName Имя файла после копирования.
     * @return Сообщение о результате операции.
     *
     * @~english
     * @brief Copying of the specified file.
     * @param newName File name after copying.
     * @return Message result.
     */
    QString copyFile(QString newName);

    /**
     * @~russian
     * @brief Переименование указанного файла.
     * @param newName Имя файла после переименования.
     * @return Сообщение о результате операции.
     *
     * @~english
     * @brief Renaming of the specified file.
     * @param newName File name after renaming.
     * @return Message result.
     */
    QString renameFile(QString newName);

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

    /**
     * @~russian
     * @brief Вспомогательная функция для получения имени файла при операциях над файлами в случае, если файл уже существует.
     *
     * Если файл не существует, то возвращается оригинальное имя файла.
     * @param fileName Первоначальное имя файла.
     * @return Итоговое имя файла.
     *
     * @~english
     * @brief Helper function for the getting new file name in the file operation if the file already exists.
     *
     * If the file does not exist, it returns the original file name.
     * @param fileName The original file name.
     * @return The final name of the file.
     */
    QString getNewName(QString fileName);

    /**
     * @~russian
     * @brief Создание директории для размещения указанного файла.
     * @param fileName Полный путь к файлу.
     * @return @c true - если директория успешно создана или уже существует;@n
     * @c false - если произошла ошибка при создании директории.
     *
     * @~english
     * @brief Create a directory to host the specified file.
     * @param fileName The full path to the file.
     * @return @c true - if the directory is successfully created or already exist;@n
     * @c false - if an error occurred while creating the directory.
     */
    bool makeDir(QString fileName);

};

#endif // FILERECORD_H
