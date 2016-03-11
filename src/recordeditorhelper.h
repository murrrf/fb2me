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

#ifndef RECORDEDITORHELPER_H
#define RECORDEDITORHELPER_H

/**
 * @file
 * @~russian
 * @brief Модуль базового класса вспомогательных классов, использующихся в окне редактирования записи о файле.
 *
 * @~english
 * @brief Module of base class of helper classes used in the window of the editing of recording file.
 */

#include <QGroupBox>
#include <QWidget>

// Forward class declarations
class QVBoxLayout;
class QHBoxLayout;
class QToolButton;
class QGroupBox;

/**
 * @~russian
 * @brief Перечисление возможных типов полей.
 *
 * @~english
 * @brief Enumeration of field types.
 */
enum FieldType
{
    ftLineEdit, ///< @~russian Текстовое поле ввода. @~english One-line text editor.
    ftSpinEdit, ///< @~russian Поле ввода целых чисел. @~english Spin box.
    ftComboBox ///< @~russian Выпадающий список. @~english Drop-down list.
};

/**
 * @~russian
 * @brief Базовый класс вспомогательных классов, использующихся в окне редактирования записи о файле.
 *
 * @~english
 * @brief Base class of helper classes used in the window of the editing of recording file.
 */
class RecordEditorHelper : public QGroupBox
{
    Q_OBJECT
public:
    /**
     * @~russian
     * @brief Конструктор класса.
     * @param index Номер элемента в массиве элементов.
     * @param parent Указатель на родительское окно.
     *
     * @~english
     * @brief Class constructor.
     * @param index Number of the element in the array elements.
     * @param parent Parent window pointer.
     */
    explicit RecordEditorHelper(int index, QWidget *parent = 0);

    /**
     * @~russian
     * @brief Деструктор класса.
     *
     * @~english
     * @brief Class destructor.
     */
    ~RecordEditorHelper();

    /**
     * @~russian
     * @brief Добавление нового поля на панель.
     * @param ft Тип поля.
     * @param label Метка поля.
     *
     * @~english
     * @brief Add new item on panel.
     * @param ft Field type.
     * @param label Filed label.
     */
    QWidget *addItem(FieldType ft, QString label);

private:
    /**
     * @~russian
     * @brief Главный менеджер размещения элементов.
     *
     * @~english
     * @brief Main layout manager.
     */
    QHBoxLayout *boxMain;

    /**
     * @~russian
     * @brief Менеджер размещения элементов левой колонки, для пользовательских элементов.
     *
     * @~english
     * @brief Layout manager for the elements of the left column, to the user elements.
     */
    QVBoxLayout *boxLeft;

    /**
     * @~russian
     * @brief Менеджер размещения элементов правой колонки, для кнопок управления.
     *
     * @~english
     * @brief Layout manager for the elements of the right column, to the control buttons.
     */
    QVBoxLayout *boxRight;

    /**
     * @~russian
     * @brief Кнопка «Переместить вверх».
     *
     * @~english
     * @brief «Move up» button.
     */
    QToolButton *btnMoveUp;

    /**
     * @~russian
     * @brief Кнопка «Переместить вниз».
     *
     * @~english
     * @brief «Move down» button.
     */
    QToolButton *btnMoveDown;

    /**
     * @~russian
     * @brief Кнопка «Удалить».
     *
     * @~english
     * @brief «Delete» button.
     */
    QToolButton *btnDelete;

    /**
     * @~russian
     * @brief Список элементов, отображающихся на панели.
     *
     * @~english
     * @brief List of fields.
     */
    QVector<QWidget *> itemList;

signals:
    /**
     * @~russian
     * @brief Сигнал «Передвинуть вверх».
     *
     * @~english
     * @brief «Move up» signal.
     */
    void MoveUp();

    /**
     * @~russian
     * @brief Сигнал «Передвинуть вниз».
     *
     * @~english
     * @brief «Move down» signal.
     */
    void MoveDown();

    /**
     * @~russian
     * @brief Сигнал «Удалить».
     *
     * @~english
     * @brief «Delete» signal.
     */
    void Delete();

public slots:

};

/**
 * @~russian
 * @brief Базовый класс вспомогательных классов-контейнеров, использующихся в окне редактирования записи о файле.
 *
 * @~english
 * @brief Base class of helper container classes used in the window of the editing of recording file.
 */
class RecordEditorHelperContainer : public QGroupBox
{
    Q_OBJECT
public:
    /**
     * @~russian
     * @brief Конструктор класса.
     * @param parent Указатель на родительское окно.
     *
     * @~english
     * @brief Class constructor.
     * @param parent Parent window pointer.
     */
    explicit RecordEditorHelperContainer(QWidget *parent = 0);

    /**
     * @~russian
     * @brief Деструктор класса.
     *
     * @~english
     * @brief Class destructor.
     */
    ~RecordEditorHelper();

private:
}

#endif // RECORDEDITORHELPER_H
