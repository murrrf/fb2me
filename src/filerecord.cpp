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

#ifndef MINIZ_HEADER_FILE_ONLY
#define MINIZ_HEADER_FILE_ONLY
#endif
#include "3rdparty/miniz.h"

#include <QStringList>
#include <QDir>

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

QString FileRecord::unzipFile()
{
    mz_bool status;
    mz_zip_archive archive;
    memset(&archive, 0, sizeof(archive));
    status = mz_zip_reader_init_file(&archive, filename.toStdString().c_str(), 0);

    if (status < MZ_OK)
    {
        return(trUtf8("Cannot open archive %1").arg(filename));
    }

    if (mz_zip_reader_get_num_files(&archive) != 1)
    {
        return(trUtf8("The archive %1 more than one file, or no files in the archive").arg(filename));
    }

    mz_zip_archive_file_stat file_stat;
    status = mz_zip_reader_file_stat(&archive, 0, &file_stat);

    if (status < MZ_OK)
    {
        mz_zip_reader_end(&archive);
        return(trUtf8("Error reading the archive %1").arg(filename));
    }

    QFileInfo tmp(filename);
    QString resultFileName = QDir::toNativeSeparators(QString(tmp.canonicalPath() + "/" + file_stat.m_filename));
    status = mz_zip_reader_extract_file_to_file(&archive, file_stat.m_filename, resultFileName.toStdString().c_str(), 0);

    if (status < MZ_OK)
    {
        return(trUtf8("Error extracting file %2 from archive %1").arg(filename, QString(file_stat.m_filename)));
    }

    mz_zip_reader_end(&archive);

    QString oldFileName = filename;
    setFileName(resultFileName);
    qint64 oldSize = getSize();
    setSize(tmp.size());
    setIsArchive(false);

    return(trUtf8("Archive %1 succesfully unzipped (%2 -> %3)").arg(oldFileName, QString::number(oldSize),
                                                                    QString::number(getSize())));
}

QString FileRecord::zipFile()
{
    mz_bool status;
    mz_zip_archive archive;
    memset(&archive, 0, sizeof(archive));
    QString archivename = QString(filename + ".zip");
    QFileInfo tmp(archivename);

    if (tmp.exists())
    {
// TODO Add code for generate new filename if archive already exist
    }

    status = mz_zip_writer_init_file(&archive, archivename.toStdString().c_str(), 0);

    if (status < MZ_OK)
    {
        return(trUtf8("Cannot create archive %1").arg(archivename));
    }

    status = mz_zip_writer_add_file(&archive, archivename.toStdString().c_str(), filename.toStdString().c_str(), "",
                                    (mz_uint16)strlen(""), MZ_BEST_COMPRESSION);

    if (status < MZ_OK)
    {
        mz_zip_writer_finalize_archive(&archive);
        mz_zip_writer_end(&archive);
        return(trUtf8("Cannot compress file %2  to archive %1").arg(archivename, filename));
    }

    mz_zip_writer_finalize_archive(&archive);
    mz_zip_writer_end(&archive);
    return(trUtf8("File %1 successfully ziped").arg(filename));
}


