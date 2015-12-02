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

#ifndef FB2RECORD_H
#define FB2RECORD_H

/**
 * @file
 * @~russian
 * @brief Модуль единичной записи метаданных.
 *
 * @~english
 * @brief Module of single metadata record.
 */

#include <QString>
#include <QVector>

// Forward declarations
class Person;

/**
 * @~russian
 * @brief Перечисление возможных статусов записи.
 *
 * @~english
 * @brief Enumeration of statuses of the record.
 */
enum Status
{
    stNormalRecord, ///< @~russian Нормальная запись. @~english Normal record.
    stIncorrectAuthorField, ///< @~russian Поле «Автор» не соответствует стандарту. @~english Non-standard «Author» field.
    stMixedCyrLat ///< @~russian В строке, составленной из имени автора и названия книги, смешаны кириллица и латиница. @~english Mixed cyrillic and latin symbols in author and title.
};

/**
 * @~russian
 * @brief Класс единичной записи метаданных.
 *
 * @~english
 * @brief Single metadata record class.
 */
class FB2Record
{
public:
    /**
     * @~russian
     * @brief Конструктор записи.
     *
     * @~english
     * @brief Constructor of a record.
     */
    FB2Record();

    /**
     * @~russian
     * @brief Деструктор записи.
     *
     * @~english
     * @brief Destructor of a record.
     */
//    ~FB2Record();

private:
    /*
     * @~russian
     * @brief
     *
     * @~english
     * @brief
     */
    /**
     * @~russian
     * @brief Состояние записи - для различных отображений.
     *
     * @~english
     * @brief Status of the record.
     */
    Status status;

    /**
     * @~russian
     * @brief Название книги.
     *
     * Всегда существует в единственном экземпляре.
     *
     * @~english
     * @brief Book title.
     *
     * Always single, not two titles.
     */
    QString BookTitle;

};

/**
 * @~russian
 * @brief Класс описания автора
 *
 * Содержит информацию об авторе книги, документа и т.п., заданную в соответствии со спецификацией формата.
 *
 * @~english
 * @brief Person description class.
 *
 * It contains information about the author of the book, file, etc., accordingly the format specification.
 */
class Person
{
public:
    /**
     * @~russian
     * @brief Конструктор класса описания.
     *
     * @~english
     * @brief Class constructor.
     */
    Person();

    /**
     * @~russian
     * @brief Конструктор класса описания.
     *
     * Создается запись об авторе на основании имени и фамилии.
     *
     * @~english
     * @brief Class constructor.
     */
    Person(QString firstName, QString lastName);

    /**
     * @~russian
     * @brief Конструктор класса описания.
     *
     * Создается запись об авторе на основании псевдонима.
     *
     * @~english
     * @brief Class constructor.
     */
    Person(QString nickName);

private:

    /**
     * @~russian
     * @brief Статус описания.
     *
     * @c true - при отсутствии ошибок,@n
     * @c false - в случае несоответствия записи спецификации.
     *
     * @~english
     * @brief Status of description.
     *
     * @c true - in the absence of errors, @n
     * @c false - in the case of non-compliance recording specification.
     */
    bool isCorrect;

    /**
     * @~russian
     * @brief Имя.
     *
     * Один, обязателен при отсутствии <nickname>, иначе опционально.
     *
     * @~english
     * @brief First name.
     *
     * One required in the absence of <nickname>, otherwise optional.
     */
    QString first_name;

    /**
     * @~russian
     * @brief Отчество.
     *
     * Один, опционально.
     *
     * @~english
     * @brief Middle name.
     *
     * One, optional.
     */
    QString middle_name;

    /**
     * @~russian
     * @brief Фамилия.
     *
     * Один, обязателен при отсутствии <nickname>, иначе опционально.
     *
     * @~english
     * @brief Last name.
     *
     * One required in the absence of <nickname>, otherwise optional.
     */
    QString last_name;

    /**
     * @~russian
     * @brief Псевдоним.
     *
     * Один, обязателен при отсутствии <first-name> и <last-name>, иначе опционально.
     *
     * @~english
     * @brief Nickname.
     *
     * One required in the absence of mandatory <first-name> and <last-name>, otherwise optional.
     */
    QString nickname;

    /**
     * @~russian
     * @brief Домашняя страница.
     *
     * Любое число, опционально.
     *
     * @~english
     * @brief Home page.
     *
     * Any number, optional.
     */
    QVector<QString> home_page;

    /**
     * @~russian
     * @brief E-Mail.
     *
     * Любое число, опционально.
     *
     * @~english
     * @brief E-mail.
     *
     * Any number, optional.
     */
    QVector<QString> email;

    /**
     * @~russian
     * @brief Идентификатор автора.
     *
     * Один, опционально. Назначается библиотекой.
     *
     * @~english
     * @brief The author identifier.
     *
     * One, optional. Assigned from library.
     */
    QString id;
};

#endif // FB2RECORD_H
