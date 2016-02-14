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

#include <QDialog>

// Forward class declarations
class QVBoxLayout;
class QDialogButtonBox;
class QLabel;
class QLineEdit;
class QPushButton;
class QGroupBox;

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
     *
     * @~english
     * @brief Constructor of class of display information about the author.
     * @param author Record about author.
     * @param index Number of entries about the author in the author list.
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
     * @brief Поле «Имя автора».
     *
     * @~english
     * @brief First name of author field.
     */
    QLineEdit *edtFirstName;

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

#endif // RECORDEDITOR_H
