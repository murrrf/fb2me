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

#include "filerecord.h"

/**
 * @~russian
 * @brief Перечисление полей записи.
 *
 * @~english
 * @brief Enumeration of fields of the record.
 */
enum Columns
{
    colCheckColumn, ///< @~russian Псевдополе - столбец с флажком. @~english Pseudofield - column with checkbox.
    colBookTitle, ///< @~russian Поле «Название книги». @~english Book title field.
    colBookAuthor, ///< @~russian Поле «Автор(ы) книги». @~english List of book authors field.
    colSeries, ///< @~russian Поле «Серия». @~english Series field.
    colGenres, ///< @~russian Поле «Жанр». @~english Genres field.
    colEncoding, ///< @~russian Поле «Кодировка». @~english Encoding field.
    colIsArchive, ///< @~russian Поле «Сжатый файл». @~english Is File Compressed field.
    colFileSize, ///< @~russian Поле «Размер файла». @~english File size field.
    colCounterField ///< @~russian Псевдополе - маркер конца перечисления. @warning Не использовать его иным образом! @~english Pseudofield - end marker listing. @warning Do not use it otherwise!
};

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

    /**
     * @~russian
     * @brief Установка пользовательского значения в ячейку таблицы.
     *
     * Применяется только для изменения состояния записи (выбранная/невыбранная),
     * так как все остальные значения редактируются через отдельное диалоговое окно.
     * @param index Ячейка таблицы.
     * @param value Устанавливаемое значение.
     * @param role Обрабатываемое событие.
     * @return Результат установки значения:@n
     * @c true - в случае успеха;@n
     * @c false - в случае ошибки.
     *
     * @~english
     * @brief Setting custom values in a table cell.
     *
     * It applies only to change the recording state (selected / unselected),
     * since all other values are edited through a separate dialog box.
     * @param index Table cell.
     * @param value Setting value.
     * @param role Handled role.
     * @return The result of setting values:@n
     * @c true - if successful;@n
     * @c false - in case of error.
     */
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);

    /**
     * @~russian
     * @brief Получить запись, соответствующую указанному индексу модели.
     * @param index Индекс возвращаемой записи.
     * @return Искомая запись.
     *
     * @~english
     * @brief Get a record corresponding to the specified index model.
     * @param index The index of the returned record.
     * @return The desired entry.
     */
    FileRecord getRecord(const QModelIndex &index);

    /**
     * @~russian
     * @brief Получить количество выбранных записей.
     * @return Количество записей.
     *
     * @~english
     * @brief Get the number of selected records.
     * @return Number of records.
     */
    int getSelectedRecordsCount();

    /**
     * @~russian
     * @brief Получить общее количество записей в таблице.
     * @return Количество записей.
     *
     * @~english
     * @brief Get the total number of records in table.
     * @return Number of records.
     */
    int getRecordsCount();

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

    /**
     * @~russian
     * @brief Отсылка сообщения об ошибке в журнал сообщений.
     * @param msg Текст сообщения.
     *
     * @~english
     * @brief Sending error messages to the message log.
     * @param msg Message text.
     */
    void ErrorMessage(const QString &msg);

    /**
     * @~russian
     * @brief Отсылка количества помеченных записей.
     * @param count Количество помеченных записей.
     *
     * @~english
     * @brief Sending number of marked records.
     * @param count Number of market records.
     */
    void SetSelected(int count);

    /**
     * @~russian
     * @brief Сигнал «Переместить и переименовать по шаблону».
     * @param basedir Базовая директория для перемещения файлов.
     * @param pattern Шаблон переименования.
     *
     * @~english
     * @brief «Move and rename according to the template» signal.
     * @param basedir The base directory for moving files.
     * @param pattern Renaming template.
     */
    void MoveTo(QString basedir, QString pattern);

    /**
     * @~russian
     * @brief Сигнал «Копировать и переименовать по шаблону».
     * @param basedir Базовая директория для копирования файлов.
     * @param pattern Шаблон переименования.
     *
     * @~english
     * @brief «Copy and rename according to the template» signal.
     * @param basedir The base directory for copying files.
     * @param pattern Renaming template.
     */
    void CopyTo(QString basedir, QString pattern);

    /**
     * @~russian
     * @brief Сигнал «Переименовать на месте по шаблону».
     * @param basedir Не используется, оставлен для единообразия.
     * @param pattern Шаблон переименования.
     *
     * @~english
     * @brief «In-place rename according to the template» signal.
     * @param basedir Not used.
     * @param pattern Renaming template.
     */
    void InplaceRename(QString basedir, QString pattern);


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
    void onAppendRecord(const FileRecord &record);

    /**
     * @~russian
     * @brief Обработчик сигнала «Распаковать отмеченные файлы».
     *
     * @~english
     * @brief Unzip selected files action handler.
     */
    void onUnzipSelected();

    /**
     * @~russian
     * @brief Обработчик сигнала «Распаковать выбранный файл».
     *
     * @~english
     * @brief Unzip current file action handler.
     */
    void onUnzipCurrent();

    /**
     * @~russian
     * @brief Обработчик сигнала «Запаковать отмеченные файлы».
     *
     * @~english
     * @brief Zip selected files action handler.
     */
    void onZipSelected();

    /**
     * @~russian
     * @brief Обработчик сигнала «Запаковать выбранный файл».
     *
     * @~english
     * @brief Zip current file action handler.
     */
    void onZipCurrent();

    /**
     * @~russian
     * @brief Обработчик сигнала «Отметить все файлы» меню «Выбор».
     *
     * @~english
     * @brief Select All Files action handler.
     */
    void onSelectAll();

    /**
     * @~russian
     * @brief Обработчик сигнала «Отметить только архивы» меню «Выбор».
     *
     * @~english
     * @brief Select Compressed Files action handler.
     */
    void onSelectZip();

    /**
     * @~russian
     * @brief Обработчик сигнала «Обратить выделение» меню «Выбор».
     *
     * @~english
     * @brief Invert Selection action handler.
     */
    void onInvertSelection();

    /**
     * @~russian
     * @brief Обработчик сигнала «Переместить и переименовать по шаблону».
     * @param basedir Базовая директория для перемещения файлов.
     * @param pattern Шаблон переименования.
     *
     * @~english
     * @brief Handler for «Move and rename according to the template» signal.
     * @param basedir The base directory for moving files.
     * @param pattern Renaming template.
     */
    void onMoveTo(QString basedir, QString pattern);

    /**
     * @~russian
     * @brief Обработчик сигнала «Копировать и переименовать по шаблону».
     * @param basedir Базовая директория для копирования файлов.
     * @param pattern Шаблон переименования.
     *
     * @~english
     * @brief Handler for «Copy and rename according to the template» signal.
     * @param basedir The base directory for copying files.
     * @param pattern Renaming template.
     */
    void onCopyTo(QString basedir, QString pattern);

    /**
     * @~russian
     * @brief Обработчик сигнала «Переименовать на месте по шаблону».
     * @param basedir Не используется, оставлен для единообразия.
     * @param pattern Шаблон переименования.
     *
     * @~english
     * @brief Handler for «In-place rename according to the template» signal.
     * @param basedir Not used.
     * @param pattern Renaming template.
     */
    void onInplaceRename(QString basedir, QString pattern);

    /**
     * @~russian
     * @brief Обработчик сигнала «Очистить список файлов» меню «Файл».
     *
     * @~english
     * @brief Clear file list action handler.
     */
    void onClearList();

private:
    /**
     * @~russian
     * @brief Хранилище данных модели.
     *
     * @~english
     * @brief Storage of model data.
     */
    QVector<FileRecord> Data;

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

    /**
     * @~russian
     * @brief Получение и форматирование списка серий записи.
     * @param index Индекс записи в хранилище данных модели.
     * @return Форматированная строка со списком серий.
     *
     * @~english
     * @brief Getting and formatting a list of series recording.
     * @param index The index of record in the data storage.
     * @return Formatted string with a list of series.
     */
    QString getFormattedSeriesList(int index) const;

    /**
     * @~russian
     * @brief Определение, является ли запись помеченной.
     * @param index Элемент модели, для которого определяется состояние записи.
     * @return Состояние записи.
     *
     * @~english
     * @brief Determining whether an entry is marked.
     * @param index Model index for which state of the record is determined.
     * @return State of the record.
     */
    Qt::CheckState getState(const QModelIndex &index) const;

    /**
     * @~russian
     * @brief Общее количество помеченных записей.
     *
     * @~english
     * @brief Number of marked records.
     */
    int cntSelectedRecords;

    /**
     * @~russian
     * @brief Подстановка значений полей записи в строку нового имени переименовываемого файла.
     *
     * Поскольку для удобства пользовательского редактирования строка шаблона состоит из человекопонятных подстановок,
     * для формирования итогового имени переименуемого файла требуется подставить значения полей записи в шаблон.
     * @param pattern Строка шаблона.
     * @param record Запись с данными.
     * @return Итоговая строка имени файла.
     *
     * @~english
     * @brief Substituting the values of record fields in the string of new filename.
     *
     * As for the convenience of the user edit the template line consists of clear human substitutions,
     * to form the final name of the file being renamed is required to substitute the values of the fields in the template.
     *
     * @param pattern The template string.
     * @param record Data record.
     * @return The result filename string.
     */
    QString fromTemplateToPath(const QString &pattern, const FileRecord &record);

    /**
     * @~russian
     * @brief Удаление опциональных параметров из строки имени файла.
     *
     * Параметры, взятые в квадратные скобки, являются необязательными и заполняются только при наличии.
     * Весь текст в квадратных скобках вокруг параметра удаляется, если это не затрагивает другие параметры.
     * @param path Строка имени файла.
     * @param param Заменяемый опциональный параметр.
     * @param subst Подставляемая строка - значение параметра.
     * @return Строка имени файла с подставленным значением параметра.
     *
     * @~english
     * @brief Removing the optional parameters of the file name string.
     *
     * The parameters in brackets are optional and should be completed only if there is.
     * All of the text in square brackets around the parameter is removed, if it does not affect the other parameters.
     * @param path Filename string.
     * @param param Replacement optional parameter.
     * @param subst Substituted string - value of the parameter.
     * @return File name string with a substituted value of the parameter.
     */
    QString fromPathRemoveOptional(QString &path, const QString &param, const QString &subst);

};

#endif // TABLEMODEL_H
