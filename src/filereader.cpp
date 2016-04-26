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

#include "filereader.h"

#include <QDirIterator>
#include <QFileInfo>
#include <QXmlStreamReader>

#include "../3rdparty/miniz.h"

#include <QDebug>

FileReader::FileReader(QStringList files)
{
    filenames.clear();
    QStringList::iterator it;

    for (it = files.begin(); it != files.end(); ++it)
    {
        filenames.append(*it);
    }
}

FileReader::FileReader(QString dir, bool recursive)
{
    filenames.clear();

    QStringList ext = QStringList() << "*.fb2" << "*.fb2.zip";
    QDir::Filters filters = QDir::NoDotAndDotDot | QDir::Files;

    if (recursive)
    {
        QDirIterator it(dir, ext, filters, QDirIterator::Subdirectories);

        while (it.hasNext())
        {
            filenames.append(it.next());
        }
    }
    else
    {
        QDirIterator it(dir, ext, filters);

        while (it.hasNext())
        {
            filenames.append(it.next());
        }
    };
}

void FileReader::run()
{
    QStringList::iterator it;

    for (it = filenames.begin(); it != filenames.end(); ++it)
    {
        FileRecord *rec = new FileRecord();
        QFileInfo f(*it);

        if ((f.isFile()) && (!f.isSymLink()))
        {
            rec->setSize(f.size());
            rec->setFileName(f.canonicalFilePath());
            rec->setIsArchive(isFileArchive(*it));
            parseFile((*it), *rec);
        }

        emit AppendRecord(*rec);
        delete rec;
    }
}

bool FileReader::isFileArchive(const QString &filename)
{
    QFileInfo f(filename);
    return (f.suffix().toLower() == "zip");
}

void FileReader::parseFile(QString &filename, FileRecord &record)
{
    QFileInfo f(filename);
    QFile file(filename);
    QByteArray data;
    QXmlStreamReader reader;

    if (f.suffix() == "fb2")
    {
        if (!file.open(QFile::ReadOnly | QFile::Text))
        {
            return;
        }

        reader.setDevice(&file);
    }
    else
        if (f.suffix() == "zip")
        {
            int res = unzipFile(filename, data);

            if (0 != res)
            {
                return;
            }

            reader.addData(data);
        }

    reader.readNext();

    if (reader.isStartDocument())
    {
        record.setEncoding(reader.documentEncoding().toString());
    }

    if (reader.readNextStartElement())
    {
        if (reader.name() == "FictionBook")
        {
            if (reader.readNextStartElement())
            {
                if (reader.name() == "description")
                {
                    if (reader.readNextStartElement())
                    {
                        if (reader.name() == "title-info")
                        {
                            while (reader.readNextStartElement())
                            {
                                if (reader.name() == "genre")
                                {
                                    QString genre = reader.readElementText();

                                    if (reader.attributes().hasAttribute("match"))
                                    {
                                        int match = reader.attributes().value("match").toInt();
                                        record.addGenre(genre, match);
                                    }
                                    else
                                        record.addGenre(genre);
                                }
                                else
                                    if (reader.name() == "author")
                                    {
                                        Person *tmpAuthor = new Person();

                                        while (reader.readNextStartElement())
                                        {
                                            if (reader.name() == "first-name")
                                            {
                                                tmpAuthor->setFirstName(reader.readElementText());
                                            }

                                            if (reader.name() == "middle-name")
                                            {
                                                tmpAuthor->setMiddleName(reader.readElementText());
                                            }

                                            if (reader.name() == "last-name")
                                            {
                                                tmpAuthor->setLastName(reader.readElementText());
                                            }

                                            if (reader.name() == "nickname")
                                            {
                                                tmpAuthor->setNickname(reader.readElementText());
                                            }

                                            if (reader.name() == "home-page")
                                            {
                                                tmpAuthor->addHomePage(reader.readElementText());
                                            }

                                            if (reader.name() == "email")
                                            {
                                                tmpAuthor->addEmail(reader.readElementText());
                                            }

                                            if (reader.name() == "id")
                                            {
                                                tmpAuthor->setId(reader.readElementText());
                                            }
                                        }

                                        record.addAuthor(*tmpAuthor);
                                        delete tmpAuthor;
                                    }
                                    else
                                        if (reader.name() == "book-title")
                                        {
                                            record.setBookTitle(reader.readElementText());
                                        }
                                        else
                                            if (reader.name() == "sequence")
                                            {
                                                if (reader.attributes().hasAttribute("name"))
                                                {
                                                    QString sequence = reader.attributes().value("name").toString();

                                                    if (reader.attributes().hasAttribute("number"))
                                                    {
                                                        int number = reader.attributes().value("number").toInt();
                                                        record.addSequence(sequence, number);
                                                    }
                                                    else
                                                        record.addSequence(sequence);
                                                }
                                            }
                                            else reader.skipCurrentElement();
                            }
                        }
                    }
                }
            }
        }
    }

    file.close();
}

int FileReader::unzipFile(QString &filename, QByteArray &file)
{
    mz_bool status;
    mz_zip_archive archive;
    memset(&archive, 0, sizeof(archive));
    status = mz_zip_reader_init_file(&archive, filename.toStdString().c_str(), 0);

    if (status < MZ_OK)
        return status;

    if (mz_zip_reader_get_num_files(&archive) != 1)
    {
        emit ErrorMessage(tr("The archive %1 more than one file, or no files in the archive").arg(filename));
        return MZ_PARAM_ERROR;
    }

    mz_zip_archive_file_stat file_stat;
    status = mz_zip_reader_file_stat(&archive, 0, &file_stat);

    if (status < MZ_OK)
    {
        emit ErrorMessage(tr("Error reading the file %1").arg(filename));
        mz_zip_reader_end(&archive);
        return MZ_PARAM_ERROR;
    }

    size_t uncompressed_size = file_stat.m_uncomp_size;
    void *p = mz_zip_reader_extract_file_to_heap(&archive, file_stat.m_filename, &uncompressed_size, 0);

    if (!p)
    {
        emit ErrorMessage(tr("Error extracting file %1").arg(filename));
        mz_zip_reader_end(&archive);
        return MZ_PARAM_ERROR;
    }

    file.append(static_cast<char *>(p));
    mz_zip_reader_end(&archive);
    return 0;
}
