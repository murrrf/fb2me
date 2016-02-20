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

#include <QWidget>

/**
 * @~russian
 * @brief Базовый класс вспомогательных классов, использующихся в окне редактирования записи о файле.
 *
 * @~english
 * @brief Base class of helper classes used in the window of the editing of recording file.
 */class RecordEditorHelper : public QWidget
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
    explicit RecordEditorHelper(QWidget *parent = 0);
    /**
     * @~russian
     * @brief Деструктор класса.
     *
     * @~english
     * @brief Class destructor.
     */
    ~RecordEditorHelper();

signals:

public slots:

};

#endif // RECORDEDITORHELPER_H
