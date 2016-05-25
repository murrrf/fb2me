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

#include "tablemodel.h"
#include <QDir>

const char lbracket =
    '{'; // Left and right brackets for optional parameters. Should be moved to a more appropriate place.
const char rbracket = '}';

TableModel::TableModel(QObject *parent): QAbstractTableModel(parent)
{
    cntSelectedRecords = 0;
    connect(this, SIGNAL(MoveTo(QString, QString)), this, SLOT(onMoveTo(QString, QString)));
    connect(this, SIGNAL(CopyTo(QString, QString)), this, SLOT(onCopyTo(QString, QString)));
    connect(this, SIGNAL(InplaceRename(QString, QString)), this, SLOT(onInplaceRename(QString, QString)));
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
                return tr("yes");
            }
            else
            {
                return tr("no");
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
                return tr("Book title");
                break;

            case colBookAuthor:
                return tr("Book author");
                break;

            case colSeries:
                return tr("Series");
                break;

            case colGenres:
                return tr("Genres");
                break;

            case colEncoding:
                return tr("Encoding");
                break;

            case colIsArchive:
                return tr("Archived");
                break;

            case colFileSize:
                return tr("File size");
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
            cntSelectedRecords++;
            emit SetSelected(cntSelectedRecords);
            return true;
        }
        else
        {
            Data[index.row()].setSelected(false);
            cntSelectedRecords--;
            emit SetSelected(cntSelectedRecords);
            return true;
        }
    }

    return false;
}

FileRecord TableModel::getRecord(const QModelIndex &index)
{
    return Data.value(index.row());
}

int TableModel::getSelectedRecordsCount()
{
    return cntSelectedRecords;
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
    emit EventMessage(tr("File \"%1\" added").arg(record.getFileName()));
    // TODO Replace QVector to QMap for avoiding record duplication
}

void TableModel::onUnzipSelected()
{
    QVector<FileRecord>::iterator it;
    QString result;

    for (it = Data.begin(); it != Data.end(); ++it)
    {
        if ((*it).isSelected())
        {
            if (!(*it).isArchive())
            {
                emit EventMessage(tr("File %1 already uncompressed").arg((*it).getFileName()));
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
        emit EventMessage(tr("File %1 already uncompressed").arg(Data.value(ind.row()).getFileName()));
}

void TableModel::onZipSelected()
{
    QVector<FileRecord>::iterator it;
    QString result;

    for (it = Data.begin(); it != Data.end(); ++it)
    {
        if ((*it).isSelected())
        {
            if ((*it).isArchive())
            {
                emit EventMessage(tr("File %1 already compressed").arg((*it).getFileName()));
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
        emit EventMessage(tr("File %1 already compressed").arg(Data.value(ind.row()).getFileName()));
}

void TableModel::onSelectAll()
{
    QVector<FileRecord>::iterator it;

    for (it = Data.begin(); it != Data.end(); ++it)
    {
        (*it).setSelected(true);
    }

    cntSelectedRecords = Data.size();
    emit SetSelected(cntSelectedRecords);
}

void TableModel::onSelectZip()
{
    QVector<FileRecord>::iterator it;
    cntSelectedRecords = 0;

    for (it = Data.begin(); it != Data.end(); ++it)
    {
        (*it).setSelected((*it).isArchive());

        if ((*it).isSelected())
            cntSelectedRecords++;
    }

    emit SetSelected(cntSelectedRecords);
}

void TableModel::onInvertSelection()
{
    QVector<FileRecord>::iterator it;
    cntSelectedRecords = 0;

    for (it = Data.begin(); it != Data.end(); ++it)
    {
        (*it).setSelected(!(*it).isSelected());

        if ((*it).isSelected())
            cntSelectedRecords++;
    }

    emit SetSelected(cntSelectedRecords);
}

void TableModel::onMoveTo(QString basedir, QString pattern)
{
    QVector<FileRecord>::iterator it;

    for (it = Data.begin(); it != Data.end(); ++it)
    {
        if ((*it).isSelected())
        {
            QString newPath = fromTemplateToPath(pattern, (*it));
            emit EventMessage((*it).moveFile(basedir + QDir::separator() + newPath));
        }
    }
}

void TableModel::onCopyTo(QString basedir, QString pattern)
{
    QVector<FileRecord>::iterator it;

    for (it = Data.begin(); it != Data.end(); ++it)
    {
        if ((*it).isSelected())
        {
            QString newPath = fromTemplateToPath(pattern, (*it));
            emit EventMessage((*it).copyFile(basedir + QDir::separator() + newPath));
        }
    }
}

void TableModel::onInplaceRename(QString basedir, QString pattern)
{
    Q_UNUSED(basedir)

    QVector<FileRecord>::iterator it;

    for (it = Data.begin(); it != Data.end(); ++it)
    {
        if ((*it).isSelected())
        {
            QString oldPath = QFileInfo((*it).getFileName()).absolutePath();
            QString newPath = oldPath + QDir::separator() + fromTemplateToPath(pattern, (*it));
            emit EventMessage((*it).renameFile(newPath));
        }
    }
}

void TableModel::onClearList()
{
    emit onBeginReading();
    Data.clear();
    emit onEndReading();
}

QString TableModel::getFormattedGenresList(int index) const
{
    QStringList res;
    genre_t tmp = Data.value(index).getGenresList();
    genre_t::iterator it;

    for (it = tmp.begin(); it != tmp.end(); ++it)
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

    for (it = tmp.begin(); it != tmp.end(); ++it)
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

QString TableModel::fromTemplateToPath(const QString &pattern, const FileRecord &record)
{
    QString result = pattern;
    Person author = record.getAuthor(0);

    // TODO Add event processing when the specified nickname instead of a name and surname

    fromPathRemoveOptional(result, "%A", author.getFirstLetterOfLastName());
    fromPathRemoveOptional(result, "%F", author.getFirstName());
    fromPathRemoveOptional(result, "%M", author.getMiddleName());
    fromPathRemoveOptional(result, "%L", author.getLastName());
    fromPathRemoveOptional(result, "%B", record.getBookTitle());

    QString sequence;
    QString number;

    if (!record.getSequenceList().empty())
    {
        sequence = record.getSequenceList().at(0).first;
        number = QString::number(record.getSequenceList().at(0).second);

        if (number == "0")
            number = "";
    }
    else
    {
        sequence = "";
        number = "";
    }

    fromPathRemoveOptional(result, "%S", sequence);
    fromPathRemoveOptional(result, "%N", number);

    result.replace(lbracket, "");
    result.replace(rbracket, "");
    result.replace(QString(2, QDir::separator()), QDir::separator());
    result.replace("  ", " ");

    result += ".fb2";

    if (record.isArchive())
        result += ".zip";

    return result;
}

QString TableModel::fromPathRemoveOptional(QString &path, const QString &param, const QString &subst)
{
    // TODO There must be an easier way the replacement of optional parameters
    if (subst.isEmpty())
    {
        while (path.contains(param))
        {
            int posFirstName = path.indexOf(param);
            int posRightBracket = path.indexOf(rbracket, posFirstName);
            int posRightLeftBracket = path.indexOf(lbracket, posFirstName);

            if (posRightLeftBracket == -1)
            {
                posRightLeftBracket = path.length();
            }

            int posLeftBracket = path.lastIndexOf(lbracket, posFirstName);
            int posLeftRightBracket = path.lastIndexOf(rbracket, posFirstName);

            if (posLeftRightBracket == -1)
            {
                posLeftRightBracket = 0;
            }

            int posRightParam = path.indexOf("%", posFirstName);
            int posLeftParam = path.lastIndexOf("%", posFirstName);

            if ((posLeftBracket != -1) && (posRightBracket != -1) &&
                    (posRightBracket < posRightLeftBracket) &&
                    (posLeftBracket > posLeftRightBracket))
            {
                if (!(((posLeftParam == -1) || (posLeftParam < posLeftBracket)) &&
                        ((posRightParam == -1) || (posRightParam > posRightBracket))))
                {
                    path.remove(posLeftBracket, posRightBracket - posLeftBracket);
                }
            }
            else
            {
                path.remove(posFirstName, param.length());
            }
        }
    }
    else
    {
        path.replace(param, subst);
    }

    return path;
}
