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

#include "fb2record.h"

FB2Record::FB2Record()
{
    archived = false;
}

void FB2Record::setSize(qint64 Size)
{
    size = Size;
}

qint64 FB2Record::getSize()
{
    return size;
}

void FB2Record::setFileName(const QString &Filename)
{
    filename = Filename;
}

QString FB2Record::getFileName() const
{
    return filename;
}

void FB2Record::setIsArchive(bool IsArchive)
{
    archived = IsArchive;
}

bool FB2Record::isArchive()
{
    return archived;
}

void FB2Record::setBookTitle(QString title)
{
    BookTitle = title;
}

QString FB2Record::getBookTitle()
{
    return BookTitle;
}

void FB2Record::addGenre(QString genre_name, int genre_match)
{
    Genres.append(qMakePair(genre_name, genre_match));
}


