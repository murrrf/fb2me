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

/*
 * @file
 * @~russian
 * @brief Файл реализации для одиночной записи метаданных.
 *
 * @~english
 * @brief Source file for single metadata record.
 */

#include "filerecord.h"

#include <QStringList>

FileRecord::FileRecord()
{
    archived = false;
    selected = false;
}

void FileRecord::setSize(qint64 Size)
{
    size = Size;
}

qint64 FileRecord::getSize()
{
    return size;
}

void FileRecord::setFileName(const QString &Filename)
{
    filename = Filename;
}

QString FileRecord::getFileName() const
{
    return filename;
}

void FileRecord::setIsArchive(bool IsArchive)
{
    archived = IsArchive;
}

bool FileRecord::isArchive()
{
    return archived;
}

void FileRecord::setBookTitle(QString title)
{
    BookTitle = title;
}

QString FileRecord::getBookTitle()
{
    return BookTitle;
}

void FileRecord::addGenre(QString genre_name, int genre_match)
{
    Genres.append(qMakePair(genre_name, genre_match));
}

genre_t FileRecord::getGenresList()
{
    return Genres;

}

void FileRecord::setEncoding(QString Encoding)
{
    encoding = Encoding;
}

QString FileRecord::getEncoding() const
{
    return encoding;
}

void FileRecord::addAuthor(Person author)
{
    BookAuthor.append(author);
}

QStringList FileRecord::getAuthorList()
{
    QStringList tmp;
    QVector<Person>::iterator it;

    for (it = BookAuthor.begin(); it != BookAuthor.end(); it++)
    {
        tmp.append((*it).getFullNameLFM());
    }

    return tmp;
}

void FileRecord::addSequence(QString sequence, int number)
{
    Sequences.append(qMakePair(sequence, number));
}

sequence_t FileRecord::getSequenceList()
{
    return Sequences;
}

void FileRecord::setSelected(bool Selected)
{
    selected = Selected;
}

bool FileRecord::isSelected()
{
    return selected;
}


