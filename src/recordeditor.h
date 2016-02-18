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
     * @brief Frame of author list.Added the display of the book's authors. For some reason it does not work. It is necessary to fix it.
     */
    QGroupBox *gbxAuthorList;
    QVBoxLayout *boxAuthorList;

    /**
     * @~russian
     * @brief Список авторов.
     *
     * @~english
     * @brief List of authors.
     */
    QVector<AuthorDisplay *> authorList;

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
class AuthorDisplay : public QWidget
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

private:
    /**
     * @~russian
     * @brief Ограничивающая рамка.
     *
     * @~english
     * @brief Border frame.
     */
    QGroupBox *gbxAuthor;

    /**
     * @~russian
     * @brief Метка поля «Имя автора».
     *
     * @~english
     * @brief Label of first name of author field.
     */
    QLabel *lblFirstName;

    /**
     * @~russian
     * @brief Поле «Имя автора».
     *
     * @~english
     * @brief First name of author field.
     */
    QLineEdit *edtFirstName;

    /**
     * @~russian
     * @brief Метка поля «Отчество автора».
     *
     * @~english
     * @brief Label of middle name of author field.
     */
    QLabel *lblMiddleName;

    /**
     * @~russian
     * @brief Поле «Отчество автора».
     *
     * @~english
     * @brief Middle name of author field.
     */
    QLineEdit *edtMiddleName;

    /**
     * @~russian
     * @brief Метка поля «Фамилия автора».
     *
     * @~english
     * @brief Label of last name of author field.
     */
    QLabel *lblLastName;

    /**
     * @~russian
     * @brief Поле «Фамилия автора».
     *
     * @~english
     * @brief Last name of author field.
     */
    QLineEdit *edtLastName;

    /**
     * @~russian
     * @brief Кнопка «Передвинуть автора вверх».
     *
     * @~english
     * @brief «Move up the author» button.
     */
    QPushButton *btnMoveUp;

    /**
     * @~russian
     * @brief Кнопка «Передвинуть автора вниз».
     *
     * @~english
     * @brief «Move down the author» button.
     */
    QPushButton *btnMoveDown;

    /**
     * @~russian
     * @brief Кнопка «Удалить автора».
     *
     * @~english
     * @brief «Delete this author» button.
     */
    QPushButton *btnDeleteAuthor;

signals:
    /**
     * @~russian
     * @brief Сигнал «Передвинуть автора вверх».
     *
     * @~english
     * @brief «Move up the author» signal.
     */
    void MoveAuthorUp();

    /**
     * @~russian
     * @brief Сигнал «Передвинуть автора вниз».
     *
     * @~english
     * @brief «Move down the author» signal.
     */
    void MoveAuthorDown();

    /**
     * @~russian
     * @brief Сигнал «Удалить автора».
     *
     * @~english
     * @brief «Delete this author» signal.
     */
    void DeleteAuthor();
};

/**
 * @~russian
 * @brief Вспомогательный класс для удобного отображения информации о книжной серии.
 *
 * @~english
 * @brief Helper class for convenient display of information about the book series.
 */class SeriesDisplay : public QWidget
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
     * @param author Record about the book series.
     * @param index Number of entries about the series in the series list.
     * @param parent Parent window pointer.
     */
    SeriesDisplay(sequence_t *series, int index, QWidget *parent=0);

    /**
     * @~russian
     * @brief Деструктор класса.
     *
     * @~english
     * @brief Destructor of class.
     */
    virtual ~SeriesDisplay();

private:
    /**
     * @~russian
     * @brief Ограничивающая рамка.
     *
     * @~english
     * @brief Border frame.
     */
    QGroupBox *gbxSeries;

    /**
     * @~russian
     * @brief Метка поля «Имя серии».
     *
     * @~english
     * @brief Label of series name field.
     */
    QLabel *lblSeriesName;

    /**
     * @~russian
     * @brief Поле «Имя серии».
     *
     * @~english
     * @brief Series name field.
     */
    QLineEdit *edtSeriesName;

    /**
     * @~russian
     * @brief Метка поля «Номер в серии».
     *
     * @~english
     * @brief Label of number in the series field.
     */
    QLabel *lblSeriesNumber;

    /**
     * @~russian
     * @brief Поле «Номер в серии».
     *
     * @~english
     * @brief Number in the series field.
     */
    QLineEdit *edtSeriesNumber;

    /**
     * @~russian
     * @brief Кнопка «Передвинуть серию вверх».
     *
     * @~english
     * @brief «Move up the series» button.
     */
    QPushButton *btnMoveUp;

    /**
     * @~russian
     * @brief Кнопка «Передвинуть серию вниз».
     *
     * @~english
     * @brief «Move down the series» button.
     */
    QPushButton *btnMoveDown;

    /**
     * @~russian
     * @brief Кнопка «Удалить серию».
     *
     * @~english
     * @brief «Delete this series» button.
     */
    QPushButton *btnDeleteSeries;

signals:
    /**
     * @~russian
     * @brief Сигнал «Передвинуть серию вверх».
     *
     * @~english
     * @brief «Move up the series»» signal.
     */
    void MoveSeriesUp();

    /**
     * @~russian
     * @brief Сигнал «Передвинуть серию вниз».
     *
     * @~english
     * @brief «Move down the series»» signal.
     */
    void MoveSeriesDown();

    /**
     * @~russian
     * @brief Сигнал «Удалить серию».
     *
     * @~english
     * @brief «Delete this series»» signal.
     */
    void DeleteSeries();
};

#endif // RECORDEDITOR_H
