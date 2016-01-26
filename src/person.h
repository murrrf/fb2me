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

#ifndef PERSON_H
#define PERSON_H

/**
 * @file
 * @~russian
 * @brief Модуль описания автора.
 *
 * @~english
 * @brief The module of author description.
 */

#include <QString>
#include <QVector>

/**
 * @~russian
 * @brief Класс описания автора.
 *
 * Содержит информацию об авторе книги, документа и т.п., заданную в соответствии со спецификацией формата.
 * Не является независимым классом, а лишь составной частью записи метаданных.
 *
 * @~english
 * @brief Person description class.
 *
 * It contains information about the author of the book, file, etc., accordingly the format specification.
 * It is not an independent class, but merely part of the metadata records.
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

    /**
     * @~russian
     * @brief Статус описания автора.
     *
     * @return
     * @c true - при отсутствии ошибок,@n
     * @c false - в случае несоответствия записи спецификации.
     *
     * @~english
     * @brief Status of description of the author.
     *
     * @return
     * @c true - in the absence of errors, @n
     * @c false - in the case of non-compliance recording specification.
     */
    bool isCorrect();

    /**
     * @~russian
     * @brief Получение полного имени автора.
     *
     * Имя автора, в порядке Фамилия - Имя - Отчество.
     * @return Полное имя.
     *
     * @~english
     * @brief Getting the full name of the author.
     *
     * Author's name, in order Surname - Name - Middle name.
     * @return Full name.
     */
    QString getFullNameLFM();

    /**
     * @~russian
     * @brief Получение полного имени автора.
     *
     * Имя автора, в порядке Имя - Отчество - Фамилия.
     * @return Полное имя.
     *
     * @~english
     * @brief Getting the full name of the author.
     *
     * Author's name, in order Name - Middle name - Surname.
     * @return Full name.
     */
    QString getFullNameFML();

    /**
     * @~russian
     * @brief Установка имени автора.
     * @param firstName Имя автора.
     *
     * @~english
     * @brief Set first name of the author.
     * @param firstName First name.
     */
    void setFirstName(QString firstName);

    /**
     * @~russian
     * @brief Получение имени автора.
     * @return Имя автора.
     *
     * @~english
     * @brief Get first name of the author.
     * @return First name.
     */
    QString getFirstName();

    /**
     * @~russian
     * @brief Установка отчества автора.
     * @param middleName Отчество автора.
     *
     * @~english
     * @brief Set middle name of the author.
     * @param middleName Middle name.
     */
    void setMiddleName(QString middleName);

    /**
     * @~russian
     * @brief Получение отчества автора.
     * @return Отчество автора.
     *
     * @~english
     * @brief Get middle name of the author.
     * @return Middle name.
     */
    QString getMiddleName();

    /**
     * @~russian
     * @brief Установка фамилии автора.
     * @param lastName Фамилия автора.
     *
     * @~english
     * @brief Set last name of the author.
     * @param lastName Last name.
     */
    void setLastName(QString lastName);

    /**
     * @~russian
     * @brief Получение фамилии автора.
     * @return Фамилия автора.
     *
     * @~english
     * @brief Get last name of the author.
     * @return Last name.
     */
    QString getLastName();

    /**
     * @~russian
     * @brief Получение первой буквы фамилии автора.
     * @return Первая буква фамилии автора.
     *
     * @~english
     * @brief Get first letter of the last name of the author.
     * @return First letter of the last name.
     */
    QString getFirstLetterOfLastName() const;

    /**
     * @~russian
     * @brief Установка псевдонима автора.
     * @param nickName Псевдоним автора.
     *
     * @~english
     * @brief Set nickname of the author.
     * @param nickName Nickname.
     */
    void setNickname(QString nickName);

    /**
     * @~russian
     * @brief Получение псевдонима автора.
     * @return Псевдоним автора.
     *
     * @~english
     * @brief Get nickname of the author.
     * @return Nickname.
     */
    QString getNickname();

    /**
     * @~russian
     * @brief Добавление домашней страницы автора.
     * @param homePage Домашняя страница.
     *
     * @~english
     * @brief Adding the author's home page.
     * @param homePage Home page.
     */
    void addHomePage(QString homePage);

    /**
     * @~russian
     * @brief Получение общего количества домашних страниц автора.
     * @return Количество домашних страниц.
     *
     * @~english
     * @brief Getting the total number of home pages of the author.
     * @return The number of home pages.
     */
    int getHomePageCount();

    /**
     * @~russian
     * @brief Получение домашней страницы по ее номеру в списке.
     * @param number Номер домашней страницы в списке.
     * @return Домашняя страница.
     *
     * @~english
     * @brief Getting home page by its number in the list.
     * @param number Home page number in the list.
     * @return Home page.
     */
    QString getHomePageByNumber(int number);

    /**
     * @~russian
     * @brief Получение всех домашних страниц.
     * @return Список домашних страниц.

     * @~english
     * @brief Getting all home pages.
     * @return The list of home pages.
     */
    QVector<QString> getHomePageAll();

    /**
     * @~russian
     * @brief Добавление электронной почты автора.
     * @param eMail Адрес электронной почты.
     *
     * @~english
     * @brief Adding e-mail the author.
     * @param eMail E-mail address.
     */
    void addEmail(QString eMail);

    /**
     * @~russian
     * @brief Получение общего количества адресов электронной почты автора.
     * @return Количество адресов.
     *
     * @~english
     * @brief Getting the total number of e-mail addresses of the author.
     * @return The number of addresses.
     */
    int getEmailCount();

    /**
     * @~russian
     * @brief Получение адреса электронной почты по его номеру в списке.
     * @param number Номер адреса электронной почты в списке.
     * @return Адрес электронной почты.
     *
     * @~english
     * @brief Getting e-mail addresses by its number in the list.
     * @param number Number of e-mail addresses on the list.
     * @return E-mail address.
     */
    QString getEmailByNumber(int number);

    /**
     * @~russian
     * @brief Получение всех адресов электронной почты.
     * @return Список адресов электронной почты.
     *
     * @~english
     * @brief getEmailAll
     * @return
     */
    QVector<QString> getEmailAll();

    /**
     * @~russian
     * @brief Установка идентификатора автора.
     * @param Id Идентификатор автора.
     *
     * @~english
     * @brief Set ID of the author.
     * @param Id ID.
     */
    void setId(QString Id);

    /**
     * @~russian
     * @brief Получение идентификатора автора.
     * @return Идентификатор автора.
     *
     * @~english
     * @brief Get ID of the author.
     * @return ID.
     */
    QString getId();
private:

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
     * Любое количество, опционально.
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
     * Любое количество, опционально.
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

#endif // PERSON_H
