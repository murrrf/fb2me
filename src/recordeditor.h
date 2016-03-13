/***********************************************************************
 *
 * Copyright (C) 2016 Sergej Martynov <veter@veter.name>
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

#ifndef RECORDEDITOR_H
#define RECORDEDITOR_H

/**
 * @file
 * @~russian
 * @brief Модуль окна редактирования записи о файле.
 *
 * @~english
 * @brief The module of the record editor window.
 */

#include "types.h"
#include "recordeditorhelper.h"

#include <QDialog>
#include <QWidget>

// Forward class declarations
class QVBoxLayout;
class QDialogButtonBox;
class QLabel;
class QLineEdit;
class QPushButton;
class QGroupBox;
class QGridLayout;

class FileRecord;
class Person;

class AuthorDisplay;

/**
 * @~russian
 * @brief Класс окна редактирования записи о файле.
 *
 * @~english
 * @brief The RecordEditor class.
 */
class RecordEditor : public QDialog
{
    Q_OBJECT
public:

    /**
     * @~russian
     * @brief Конструктор окна редактирования записи о файле.
     * @param rec Отображаемая в окне редактирования запись.
     * @param parent Указатель на родительское окно.
     *
     * @~english
     * @brief The record editor window constructor.
     * @param rec Record displayed in the edit dialog
     * @param parent Parent window pointer.
     */
    explicit RecordEditor(FileRecord *rec, QWidget *parent = 0);

    /**
     * @~russian
     * @brief Деструктор окна редактирования записи о файле.
     *
     * @~english
     * @brief The record editor window destructor.
     */
    ~RecordEditor();

    /**
     * @~russian
     * @brief Установка нового содержимого редактируемой записи.
     * @param rec Новая запись.
     *
     * @~english
     * @brief Setting a new content for edited recording.
     * @param rec New record.
     */
    void setData(FileRecord *rec);

private:
    /**
     * @~russian
     * @brief Менеджер размещения элементов диалога.
     *
     * @~english
     * @brief Layout manager for dialog.
     */
    QVBoxLayout *boxMain;

    /**
     * @~russian
     * @brief Менеджер размещения кнопок управления диалогом.
     *
     * @~english
     * @brief Layout manager for dialog buttons.
     */
    QDialogButtonBox *boxButtons;

    /**
     * @~russian
     * @brief Редактируемая запись.
     *
     * @~english
     * @brief Edited record.
     */
    FileRecord *record;

    /**
     * @~russian
     * @brief Метка поля отображения названия книги.
     *
     * @~english
     * @brief Label of field display the title of the book.
     */
    QLabel *lblBookTitle;

    /**
     * @~russian
     * @brief Поле отображения названия книги.
     *
     * @~english
     * @brief Field display the title of the book.
     */
    QLineEdit *edtBookTitle;

    /**
     * @~russian
     * @brief Рамка списка авторов.
     *
     * @~english
     * @brief Frame of author list.
     */
    QGroupBox *gbxAuthorList;

    /**
     * @~russian
     * @brief Менеджер размещения списка авторов.
     *
     * @~english
     * @brief Layout manager of author list.
     */
    QVBoxLayout *boxAuthorList;

    /**
     * @~russian
     * @brief Рамка списка книжных серий.
     *
     * @~english
     * @brief Frame of book series list.
     */
    QGroupBox *gbxSeriesList;

    /**
     * @~russian
     * @brief Менеджер размещения списка книжных серий.
     *
     * @~english
     * @brief Layout manager of book series list.
     */
    QVBoxLayout *boxSeriesList;

    /**
     * @~russian
     * @brief Рамка списка жанров книги.
     *
     * @~english
     * @brief Frame of book genres list.
     */
    QGroupBox *gbxGenresList;

    /**
     * @~russian
     * @brief Менеджер размещения списка жанров книги.
     *
     * @~english
     * @brief Layout manager of book genres list.
     */
    QVBoxLayout *boxGenresList;

    /**
     * @~russian
     * @brief Обновление внешнего вида диалога.
     *
     * Вызывается для перестроения диалога при изменении содержимого редактируемой записи.
     *
     * @~english
     * @brief Update the look of the dialogue.
     *
     * It called for dialogue when changing the contents edited record.
     */
    void updateUI();

signals:

public slots:

};

/**
 * @~russian
 * @brief Вспомогательный класс для удобного отображения информации об авторе.
 *
 * @~english
 * @brief Helper class for convenient display of information about the author.
 */
class AuthorDisplay : public RecordEditorHelper
{
    Q_OBJECT
public:
    /**
     * @~russian
     * @brief Конструктор класса отображения информации об авторе.
     * @param author Запись об авторе.
     * @param index Номер записи об авторе в списке авторов.
     * @param parent Указатель на родительское окно.
     *
     * @~english
     * @brief Constructor of class of display information about the author.
     * @param author Record about author.
     * @param index Number of entries about the author in the author list.
     * @param parent Parent window pointer.
     */
    explicit AuthorDisplay(Person *author, int index, QWidget *parent = 0);

    /**
     * @~russian
     * @brief Деструктор класса.
     *
     * @~english
     * @brief Destructor of class.
     */
    virtual ~AuthorDisplay();
};

/**
 * @~russian
 * @brief Вспомогательный класс для удобного отображения информации о книжной серии.
 *
 * @~english
 * @brief Helper class for convenient display of information about the book series.
 */
class SeriesDisplay : public RecordEditorHelper
{
    Q_OBJECT
public:
    /**
     * @~russian
     * @brief Конструктор класса отображения информации о книжной серии.
     * @param series Запись о книжной серии.
     * @param index Номер записи о книжной серии в списке серий.
     * @param parent Указатель на родительское окно.
     *
     * @~english
     * @brief Constructor of class of display information about the book series.
     * @param series Record about the book series.
     * @param index Number of entries about the series in the series list.
     * @param parent Parent window pointer.
     */
    SeriesDisplay(sequence_t *series, int index, QWidget *parent = 0);
    /**
     * @~russian
     * @brief Деструктор класса.
     *
     * @~english
     * @brief Destructor of class.
     */
    ~SeriesDisplay();
};

/**
 * @~russian
 * @brief Вспомогательный класс для удобного отображения информации о жанре книги.
 *
 * @~english
 * @brief Helper class for convenient display of information about the book genre.
 */
class GenresDisplay : public RecordEditorHelper
{
    Q_OBJECT
public:

    /**
     * @~russian
     * @brief Конструктор класса отображения информации о жанре книги.
     * @param genres Запись о жанре книги.
     * @param index Номер записи о жанре книги в списке жанров.
     * @param parent Указатель на родительское окно.
     *
     * @~english
     * @brief Constructor of class of display information about the book genre.
     * @param genres Record about the book genre.
     * @param index Number of entries about the genre in the genre list.
     * @param parent Parent window pointer.
     */
    GenresDisplay(genre_t *genres, int index, QWidget *parent = 0);

    /**
     * @~russian
     * @brief Деструктор класса.
     *
     * @~english
     * @brief Destructor of class.
     */
    ~GenresDisplay();
};

#endif // RECORDEDITOR_H
