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

#include "reader.h"

#include <QDirIterator>
#include <QFileInfo>
#include <QXmlStreamReader>

#include <QDebug>

Reader::Reader(QStringList files)
{
    filenames.clear();
    QStringList::iterator it;

    for (it = files.begin(); it != files.end(); it++)
    {
        filenames.append(*it);
    }
}

Reader::Reader(QString dir, bool recursive)
{
    filenames.clear();

    QStringList ext = QStringList() << "*.fb2";// << "*.fb2.zip";
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

void Reader::run()
{
    QStringList::iterator it;

    for (it = filenames.begin(); it != filenames.end(); it++)
    {
        FB2Record *rec = new FB2Record();
        QFileInfo f(*it);

        if ((f.isFile()) && (!f.isSymLink()))
        {
            rec->setSize(f.size());
            rec->setFileName(f.canonicalFilePath());
            rec->setIsArchive(isFileArchive(*it));
            // TODO Add unzipping for compressed files

            // TODO Add XML parsing
            parseFile((*it), *rec);
        }

        emit AppendRecord(*rec);
        delete rec;
    }
}

bool Reader::isFileArchive(const QString &filename)
{
    QFileInfo f(filename);
    return (f.suffix().toLower() == "zip");
}

void Reader::parseFile(QString &filename, FB2Record &record)
{
    QFile file(filename);

    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
//        qDebug() << "Cannot read file" << file.errorString();
        return;
    }

    QXmlStreamReader reader(&file);
    reader.readNext();

    if (reader.isStartDocument())
    {
        record.setEncoding(reader.documentEncoding().toString());
    }

    if (reader.readNextStartElement())
    {
        if (reader.name() == "FictionBook")
        {
            qDebug() << "FictionBook";

            if (reader.readNextStartElement())
            {
                if (reader.name() == "description")
                {
                    qDebug() << "description";

                    if (reader.readNextStartElement())
                    {
                        if (reader.name() == "title-info")
                        {
                            qDebug() << "title-info";

                        }
                    }
                }
            }
        }
    }
}
