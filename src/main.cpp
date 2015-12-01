#include "mainwindow.h"
#include <QApplication>

/**
 * @file
 * @~russian
 * @brief Главный исходный файл приложения.
 *
 * @~english
 * @brief Main application source file.
 */

/**
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
