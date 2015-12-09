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
     * @~english
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

    /**
     * @~russian
     * @brief Отсылка сообщения в журнал сообщений.
     * @param msg Текст сообщения.
     *
     * @~english
     * @brief Sending messages to the message log.
     * @param msg Message text.
     */
    void EventMessage(const QString &msg);

public slots:

    /**
     * @~russian
     * @brief Обработчик события начала чтения файлов.
     *
     * @~english
     * @brief The event handler start reading files.
     */
    void onBeginReading();

    /**
     * @~russian
     * @brief Обработчик события окончания чтения файлов.
     *
     * @~english
     * @brief The event handler finish reading files.
     */
    void onEndReading();

    /**
     * @~russian
     * @brief Обработчик события добавления новой записи в модель.
     * @param record Добавляемая запись.
     *
     * @~english
     * @brief The event handler add a new entry into the model.
     * @param record Appended record.
     */
    void onAppendRecord(const FB2Record &record);

private:
    /**
     * @~russian
     * @brief Хранилище данных модели.
     *
     * @~english
     * @brief Storage of model data.
     */
    QVector<FB2Record> Data;

    /**
     * @~russian
     * @brief Получение и форматирование списка жанров записи.
     * @param index Индекс записи в хранилище данных модели.
     * @return Форматированная строка со списком жанров.
     *
     * @~english
     * @brief Getting and formatting a list of genres recording.
     * @param index The index of record in the data storage.
     * @return Formatted string with a list of genres.
     */
    QString getFormattedGenresList(int index) const;

};

#endif // TABLEMODEL_H
