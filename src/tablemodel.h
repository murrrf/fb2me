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

class FB2Record;

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

    /**
     * @~russian
     * @brief Деструктор модели данных.
     *
     * @~english
     * @brief Destructor of a data model.
     */
//    ~TableModel();

signals:

public slots:

};

#endif // TABLEMODEL_H
