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

#ifndef TABLEMODEL_H
#define TABLEMODEL_H

/**
 * @file
 * @~russian
 * @brief Модуль модели данных.
 *
 * @~english
 * @brief The module of the data model.
 */

#include <QAbstractTableModel>
#include <QVector>

#include "fb2record.h"

/**
 * @~russian
 * @brief Класс модели данных.
 *
 * @~english
 * @brief The TableModel class.
 */
class TableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    /**
     * @~russian
     * @brief Конструктор модели данных.
     * @param parent Объект-родитель модели.
     *
     * @~english
     * @brief Constructor of a data model.
     * @param parent Parent object.
     */
    explicit TableModel(QObject *parent = 0);

    /*
     * @~russian
     * @brief Деструктор модели данных.
     *
     * @~english
     * @brief Destructor of a data model.
     */
//    ~TableModel();

    /**
     * @~russian
     * @brief Обработчик флагов ячейки.
     * @param index Ячейка таблицы.
     * @return Флаги ячейки.
     *
     * @~russian
     * @brief Cell flags handler.
     * @param index Cell of the table.
     * @return Flags.
     */
    Qt::ItemFlags flags(const QModelIndex &index) const;

    /**
     * @~russian
     * @brief Счетчик строк таблицы.
     * @param parent Таблица, для которой считаются строки.
     * @return Количество строк.
     *
     * @~english
     * @brief Table row count.
     * @param parent Table for which is considered to be number of rows.
     * @return Row count.
     */
    int rowCount(const QModelIndex &parent) const;

    /**
     * @~russian
     * @brief Счетчик столбцов таблицы.
     * @param parent Таблица, для которой считаются столбцы.
     * @return Количество строк.
     *
     * @~english
     * @brief table column count.
     * @param parent Table for which is considered to be number of columns.
     * @return Column count.
     */
    int columnCount(const QModelIndex &parent) const;

    /**
     * @~russian
     * @brief Обработчик отображения данных таблицы.
     * @param index Ячейка таблицы.
     * @param role Обрабатываемое событие.
     * @return Результат обработки.
     *
     * @~english
     * @brief Handler display of table data.
     * @param index Table cell.
     * @param role Handled role.
     * @return Displayed result.
     */
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

    /**
     * @~russian
     * @brief Обработчик отображения заголовков таблицы.
     * @param section Номер строки или столбца ячейки.
     * @param orientation Направление отображения - строки или столбцы.
     * @param role Обрабатываемое событие.
     * @return Результат обработки.
     *
     * @~english
     * @brief Handler display of table header.
     * @param section Number of row or column count.
     * @param orientation Orientation of display.
     * @param role Handled role.
     * @return Displayed result.
     */
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;


signals:

public slots:
    void onBeginReading();
    void onEndReading();

private:
    /**
     * @~russian
     * @brief Хранилище данных модели.
     *
     * @~english
     * @brief Storage of model data.
     */
    QVector<FB2Record> Data;

};

#endif // TABLEMODEL_H
