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
     * @param parent Указатель на родительское окно.
     *
     * @~english
     * @brief The record editor window constructor.
     * @param parent Parent window pointer.
     */
    explicit RecordEditor(QWidget *parent = 0);

    /**
     * @~russian
     * @brief Деструктор окна редактирования записи о файле.
     *
     * @~english
     * @brief The record editor window destructor.
     */
    ~RecordEditor();

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

signals:

public slots:

};

#endif // RECORDEDITOR_H
