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

#include <QString>
#include <QVector>
#include <QPair>
#include <QStringList>
#include <QDir>
#include <QFile>
#include <QApplication>

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

bool FileRecord::isArchive() const
{
    return archived;
}

void FileRecord::setBookTitle(QString title)
{
    BookTitle = title;
}

QString FileRecord::getBookTitle() const
{
    return BookTitle;
}

QString FileRecord::getBookTitleExt() const
{
    QString result = BookTitle;

    if (archived)
        result += ".fb2.zip";
    else
        result += ".fb2";

    return result;
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

Person FileRecord::getAuthor(int index) const
{
    return BookAuthor.at(index);
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

int FileRecord::getAuthorCount()
{
    return BookAuthor.count();
}

void FileRecord::addSequence(QString sequence, int number)
{
    Sequences.append(qMakePair(sequence, number));
}

sequence_t FileRecord::getSequenceList() const
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

    qint64 oldSize = getSize();

    if (status < MZ_OK)
    {
        return msgError(qApp->tr("Cannot open archive %1").arg(filename));
    }

    if (mz_zip_reader_get_num_files(&archive) != 1)
    {
        return msgError(qApp->tr("The archive %1 more than one file, or no files in the archive").arg(filename));
    }

    mz_zip_archive_file_stat file_stat;
    status = mz_zip_reader_file_stat(&archive, 0, &file_stat);

    if (status < MZ_OK)
    {
        mz_zip_reader_end(&archive);
        return msgError(qApp->tr("Error reading the archive %1").arg(filename));
    }

    QFileInfo tmp(filename);
    QString resultFileName = QDir::toNativeSeparators(QString(tmp.canonicalPath() + "/" + file_stat.m_filename));
    status = mz_zip_reader_extract_file_to_file(&archive, file_stat.m_filename, resultFileName.toStdString().c_str(), 0);

    if (status < MZ_OK)
    {
        return msgError(qApp->tr("Error extracting file %2 from archive %1").arg(filename,
                        QString(file_stat.m_filename)));
    }

    mz_zip_reader_end(&archive);

    QString oldFileName = filename;
    setFileName(resultFileName);
    QFileInfo tmp2(filename);
    setSize(tmp2.size());
    setIsArchive(false);
    QFile::remove(oldFileName);

    return msgResult(qApp->tr("Archive %1 succesfully unzipped (%2 -> %3)").arg(oldFileName, QString::number(oldSize),
                     QString::number(getSize())));
}

QString FileRecord::zipFile()
{
    //TODO Escape symbols in filename because files with non-valid names can't be compressed
    mz_bool status;
    mz_zip_archive archive;
    memset(&archive, 0, sizeof(archive));
    QString archiveName = QString(filename + ".zip");

    archiveName = getNewName(archiveName);

    QFileInfo tmp(archiveName);

    qint64 oldSize = getSize();

    status = mz_zip_writer_init_file(&archive, archiveName.toStdString().c_str(), 0);

    if (status < MZ_OK)
    {
        return msgError(qApp->tr("Cannot create archive %1").arg(archiveName));
    }

    status = mz_zip_writer_add_file(&archive, tmp.completeBaseName().toStdString().c_str(), filename.toStdString().c_str(),
                                    "", (mz_uint16)strlen(""), MZ_BEST_COMPRESSION);

    mz_zip_writer_finalize_archive(&archive);
    mz_zip_writer_end(&archive);

    if (status < MZ_OK)
    {
        QFile::remove(archiveName);
        return msgError(qApp->tr("Cannot compress file %2  to archive %1").arg(archiveName, filename));
    }

    QString oldFileName = getFileName();
    setFileName(archiveName);
    QFileInfo tmp2(filename);
    setSize(tmp2.size());
    setIsArchive(true);
    QFile::remove(oldFileName);

    return msgResult(qApp->tr("File %1 successfully zipped (%2 -> %3)").arg(oldFileName, QString::number(oldSize),
                     QString::number(getSize())));
}

QString FileRecord::moveFile(QString newName)
{
    newName = getNewName(newName);

    if (!makeDir(newName))
    {
        return msgError(qApp->tr("Unable to create a directory to place the file %1").arg(newName));
    }

    if (QFile::rename(getFileName(), newName))
    {
        QString result = qApp->tr("File %1 successfully moved to %2").arg(getFileName(), newName);
        setFileName(newName);
        return msgResult(result);
    }
    else
    {
        return msgError(qApp->tr("Cannot move file %1 to %2").arg(getFileName(), newName));
    }
}

QString FileRecord::copyFile(QString newName)
{
    newName = getNewName(newName);

    if (!makeDir(newName))
    {
        return msgError(qApp->tr("Unable to create a directory to place the file %1").arg(newName));
    }

    if (QFile::copy(getFileName(), newName))
    {
        QString result = qApp->tr("File %1 successfully copied to %2").arg(getFileName(), newName);
        setFileName(newName);
        return msgResult(result);
    }
    else
    {
        return msgError(qApp->tr("Cannot copy file %1 to %2").arg(getFileName(), newName));
    }
}

QString FileRecord::renameFile(QString newName)
{
    newName = getNewName(newName);

    if (!makeDir(newName))
    {
        return msgError(qApp->tr("Unable to create a directory to place the file %1").arg(newName));
    }

    if (QFile::rename(getFileName(), newName))
    {
        QString result = qApp->tr("File %1 successfully renamed to %2").arg(getFileName(), newName);
        setFileName(newName);
        return msgResult(result);
    }
    else
    {
        return msgError(qApp->tr("Cannot rename file %1 to %2").arg(getFileName(), newName));
    }
}

QString FileRecord::getNewName(QString fileName)
{
    int cntFile = 1;

    QFileInfo newFile(fileName);

    while (QFile::exists(fileName))
    {
        fileName = newFile.canonicalPath() + QDir::separator() + newFile.baseName() +
                   "(" + QString::number(cntFile) + ")" + "." + newFile.completeSuffix();
        cntFile++;
    }

    return fileName;
}

bool FileRecord::makeDir(QString fileName)
{
    QFileInfo file(fileName);
    return QDir().mkpath(file.absolutePath());
}

QString FileRecord::msgResult(QString message)
{
    return message;
}

QString FileRecord::msgError(QString message)
{
    return ("<font color=red>" + message + "</font>");
}


