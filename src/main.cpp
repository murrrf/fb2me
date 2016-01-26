/***********************************************************************
 *
 * Copyright (C) 2015 Sergej Martynov <veter@veter.name>
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

/*
 * @file
 * @~russian
 * @brief Главный исходный файл приложения.
 *
 * @~english
 * @brief Main application source file.
 */

#include "mainwindow.h"
#include <QApplication>

/*
 * @~russian
 * @brief Точка входа приложения.
 * @param argc Число аргументов командной строки.
 * @param argv Список аргументов командной строки.
 * @return Код возврата.
 *
 * @~english
 * @brief Application entry point.
 * @param argc Number of command-line arguments.
 * @param argv List of command-line arguments.
 * @return Return code.
 */
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    app.setApplicationName("FB2ME");
    app.setApplicationVersion(VERSIONSTR);
    app.setOrganizationDomain("veter.name");
    app.setOrganizationName("Veter");
    MainWindow w;
    w.show();

    return app.exec();
}
