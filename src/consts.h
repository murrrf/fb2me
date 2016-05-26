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

#ifndef CONSTS_H
#define CONSTS_H

/**
 * @file
 * @~russian
 * @brief Файл общих констант программы.
 *
 * @~english
 * @brief File of common constants.
 */

/**
 * @~russian
 * @brief Пространство имен строковых констант.
 *
 * @~english
 * @brief The namespace of string constants.
 */
namespace NAMES
{
/**
 * @~russian
 * @brief Наименование разработчика.
 * @~english
 * @brief The name of developer.
 */
const QString nameDeveloper = "Veter";
/**
 * @~russian
 * @brief Наименование приложения.
 * @~english
 * @brief The name of application.
 */
const QString nameApplication = "fb2me";
/**
 * @~russian
 * @brief Имя группы настроек «Шаблоны переименования».
 * @~english
 * @brief Name of group of settings «Templates of rename».
 */
const QString nameTemplateGroup = "Rename Templates";
/**
 * @~russian
 * @brief Имя настройки «Шаблон переименования».
 * @~english
 * @brief Name of setting «Template of rename».
 */
const QString nameTemplate = "Template";
/**
 * @~russian
 * @brief Заголовок столбца «Параметр».
 * @~english
 * @brief Column header «Parameter».
 */
const QString nameKey = "Key";
/**
 * @~russian
 * @brief Заголовок столбца «Значение».
 * @~english
 * @brief Column header «Value».
 */
const QString nameValue = "Value";
/**
 * @~russian
 * @brief Имя группы настроек «Внешние редакторы».
 * @~english
 * @brief Name of group of settings «External editors».
 */
const QString nameExtEditorGroup = "External editors";
}

#endif // CONSTS_H
