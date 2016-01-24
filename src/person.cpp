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

#include "person.h"

Person::Person()
{

}

Person::Person(QString firstName, QString lastName)
{
    first_name = firstName;
    last_name = lastName;
}

Person::Person(QString nickName)
{
    nickname = nickName;
}

bool Person::isCorrect()
{
    return (((!first_name.isEmpty()) && (!last_name.isEmpty())) || (!nickname.isEmpty()));
}

QString Person::getFullNameLFM()
{
    return QString("%1 %2 %3").arg(last_name, first_name, middle_name);
}

QString Person::getFullNameFML()
{
    return QString("%1 %2 %3").arg(first_name, middle_name, last_name);
}

void Person::setFirstName(QString firstName)
{
    first_name = firstName;
}

QString Person::getFirstName()
{
    return first_name;
}

void Person::setMiddleName(QString middleName)
{
    middle_name = middleName;
}

QString Person::getMiddleName()
{
    return middle_name;
}

void Person::setLastName(QString lastName)
{
    last_name = lastName;
}

QString Person::getLastName()
{
    return last_name;
}

QString Person::getFirstLetterOfLastName()
{
    return last_name.at(0);
}

void Person::setNickname(QString nickName)
{
    nickname = nickName;
}

QString Person::getNickname()
{
    return nickname;
}

void Person::addHomePage(QString homePage)
{
    home_page.append(homePage);
}

int Person::getHomePageCount()
{
    return home_page.count();
}

QString Person::getHomePageByNumber(int number)
{
    return home_page.at(number);
}

QVector<QString> Person::getHomePageAll()
{
    return home_page;
}

void Person::addEmail(QString eMail)
{
    email.append(eMail);
}

int Person::getEmailCount()
{
    return email.count();
}

QString Person::getEmailByNumber(int number)
{
    return email.at(number);
}

QVector<QString> Person::getEmailAll()
{
    return email;
}

void Person::setId(QString Id)
{
    id = Id;
}

QString Person::getId()
{
    return id;
}
