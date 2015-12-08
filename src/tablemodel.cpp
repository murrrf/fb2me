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
 * @brief Файл реализации для модели данных.
 *
 * @~english
 * @brief Source file for data model.
 */

#include "tablemodel.h"

TableModel::TableModel(QObject *parent): QAbstractTableModel(parent)
{
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
                return trUtf8(T_BOOKTITLE);
                break;

            case colBookAuthor:
                return trUtf8(T_BOOKAUTHOR);
                break;

            case colSeries:
                return trUtf8(T_SERIES);
                break;

            case colGenres:
                return trUtf8(T_GENRES);
                break;

            case colEncoding:
                return trUtf8(T_ENCODING);
                break;

            case colIsArchive:
                return trUtf8(T_ISARCHIVE);
                break;

            case colFileSize:
                return trUtf8(T_FILESIZE);
                break;

            default:
                break;
            }
        };
    }

    return QVariant();
}

void TableModel::onBeginReading()
{
    beginResetModel();
}

void TableModel::onEndReading()
{
    endResetModel();
}

void TableModel::onAppendRecord(const FB2Record &record)
{
    Data.append(record);
    emit EventMessage(trUtf8("File \"%1\" added").arg(record.getFileName()));
    // TODO Replace QVector to QMap for avoiding record duplication
}
