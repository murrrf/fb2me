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
 * @brief Файл реализации для модели данных.
 *
 * @~english
 * @brief Source file for data model.
 */

// TODO Add method for rename files

#include "tablemodel.h"

TableModel::TableModel(QObject *parent): QAbstractTableModel(parent)
{
    cntSelectedFiles = 0;
}

Qt::ItemFlags TableModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags tmp = Qt::NoItemFlags;

    if (index.column() == colCheckColumn)
    {
        tmp |= Qt::ItemIsUserCheckable;
    }

    tmp |= Qt::ItemIsEnabled;
    return tmp;
}

int TableModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return Data.count();
}

int TableModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return static_cast<int>(colCounterField);
}

QVariant TableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    switch (role)
    {
    case Qt::DisplayRole:
        switch (index.column())
        {
        case colBookTitle:
            return Data.value(index.row()).getBookTitle();
            break;

        case colBookAuthor:
            return Data.value(index.row()).getAuthorList().join(";\n");
            break;

        case colSeries:
            return getFormattedSeriesList(index.row());
            break;

        case colGenres:
            return getFormattedGenresList(index.row());
            break;

        case colEncoding:
            return Data.value(index.row()).getEncoding();
            break;

        case colIsArchive:
            if (Data.value(index.row()).isArchive())
            {
                return trUtf8("yes");
            }
            else
            {
                return trUtf8("no");
            }

            break;


        case colFileSize:
            return Data.value(index.row()).getSize();
            break;

        default:
            break;
        }

        break;

    case Qt::CheckStateRole:
        if (index.column() != colCheckColumn)
        {
            return QVariant();
        }

        return QVariant(static_cast<int>(getState(index)));
        break;

    default:
        break;
    }

    return QVariant();
}

QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole)
    {
        if (orientation == Qt::Horizontal)
        {
            switch (section)
            {
            case colBookTitle:
                return trUtf8("Book title");
                break;

            case colBookAuthor:
                return trUtf8("Book author");
                break;

            case colSeries:
                return trUtf8("Series");
                break;

            case colGenres:
                return trUtf8("Genres");
                break;

            case colEncoding:
                return trUtf8("Encoding");
                break;

            case colIsArchive:
                return trUtf8("Archived");
                break;

            case colFileSize:
                return trUtf8("File size");
                break;

            default:
                break;
            }
        };
    }

    return QVariant();
}

bool TableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid())
        return false;

    if (role == Qt::CheckStateRole)
    {
        if (static_cast<Qt::CheckState>(value.toInt()) == Qt::Checked)
        {
            Data[index.row()].setSelected(true);
            cntSelectedFiles++;
            emit SetSelected(cntSelectedFiles);
            return true;
        }
        else
        {
            Data[index.row()].setSelected(false);
            cntSelectedFiles--;
            emit SetSelected(cntSelectedFiles);
            return true;
        }
    }

    return false;
}

FileRecord TableModel::getRecord(const QModelIndex &index)
{
    return Data.value(index.row());
}

void TableModel::onBeginReading()
{
    beginResetModel();
}

void TableModel::onEndReading()
{
    endResetModel();
}

void TableModel::onAppendRecord(const FileRecord &record)
{
    Data.append(record);
    emit EventMessage(trUtf8("File \"%1\" added").arg(record.getFileName()));
    // TODO Replace QVector to QMap for avoiding record duplication
}

void TableModel::onUnzipSelected()
{
    QVector<FileRecord>::iterator it;
    QString result;

    for (it = Data.begin(); it != Data.end(); it++)
    {
        if ((*it).isSelected())
        {
            if (!(*it).isArchive())
            {
                emit EventMessage(trUtf8("File %1 already uncompressed").arg((*it).getFileName()));
            }
            else
            {
                result = (*it).unzipFile();
                emit EventMessage(result);
            }
        }
    }
}

void TableModel::onUnzipCurrent()
{
    QModelIndex ind = sender()->property("index").toModelIndex();

    if (Data.value(ind.row()).isArchive())
        emit EventMessage(Data[ind.row()].unzipFile());
    else
        emit EventMessage(trUtf8("File %1 already uncompressed").arg(Data.value(ind.row()).getFileName()));
}

void TableModel::onZipSelected()
{
    QVector<FileRecord>::iterator it;
    QString result;

    for (it = Data.begin(); it != Data.end(); it++)
    {
        if ((*it).isSelected())
        {
            if ((*it).isArchive())
            {
                emit EventMessage(trUtf8("File %1 already compressed").arg((*it).getFileName()));
            }
            else
            {
                result = (*it).zipFile();
                emit EventMessage(result);
            }
        }
    }
}

void TableModel::onZipCurrent()
{
    QModelIndex ind = sender()->property("index").toModelIndex();

    if (!Data.value(ind.row()).isArchive())
        emit EventMessage(Data[ind.row()].zipFile());
    else
        emit EventMessage(trUtf8("File %1 already compressed").arg(Data.value(ind.row()).getFileName()));
}

void TableModel::onSelectAll()
{
    QVector<FileRecord>::iterator it;

    for (it = Data.begin(); it != Data.end(); it++)
    {
        (*it).setSelected(true);
    }

    emit SetSelected(Data.size());
}

void TableModel::onSelectZip()
{
    QVector<FileRecord>::iterator it;
    cntSelectedFiles = 0;

    for (it = Data.begin(); it != Data.end(); it++)
    {
        (*it).setSelected((*it).isArchive());

        if ((*it).isSelected())
            cntSelectedFiles++;
    }

    emit SetSelected(cntSelectedFiles);
}

void TableModel::onInvertSelection()
{
    QVector<FileRecord>::iterator it;
    cntSelectedFiles = 0;

    for (it = Data.begin(); it != Data.end(); it++)
    {
        (*it).setSelected(!(*it).isSelected());

        if ((*it).isSelected())
            cntSelectedFiles++;
    }

    emit SetSelected(cntSelectedFiles);
}

QString TableModel::getFormattedGenresList(int index) const
{
    QStringList res;
    genre_t tmp = Data.value(index).getGenresList();
    genre_t::iterator it;

    for (it = tmp.begin(); it != tmp.end(); it++)
    {
        if ((*it).second == 100)
            res.append(QString("%1").arg((*it).first));
        else
            res.append(QString("%1 (%2\%)").arg((*it).first, QString::number((*it).second)));
    }

    return res.join(";\n");
}

QString TableModel::getFormattedSeriesList(int index) const
{
    QStringList res;
    sequence_t tmp = Data.value(index).getSequenceList();
    sequence_t::iterator it;

    for (it = tmp.begin(); it != tmp.end(); it++)
    {
        res.append(QString("%1 - %2").arg((*it).first, QString::number((*it).second)));
    }

    return res.join(";\n");
}

Qt::CheckState TableModel::getState(const QModelIndex &index) const
{
    Qt::CheckState cs = Data.value(index.row()).isSelected() ? Qt::Checked : Qt::Unchecked;
    return cs;
}
