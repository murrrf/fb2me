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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

/**
 * @file
 * @~russian
 * @brief Модуль главного окна программы.
 *
 * @~english
 * @brief The module of the main window.
 */

#include <QMainWindow>

// Forward class declarations
class QSplitter;
class QTableView;
class QTextEdit;

class TableModel;
class Reader;

/**
 * @~russian
 * @brief Класс главного окна программы.
 *
 * @~english
 * @brief The MainWindow class.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @~russian
     * @brief Конструктор главного окна.
     * @param parent Указатель на родительское окно.
     *
     * @~english
     * @brief Parent window pointer.
     * @param parent The main window constructor.
     */
    MainWindow(QWidget *parent = 0);

    /**
     * @~russian
     * @brief Деструктор главного окна.
     *
     * @~english
     * @brief The main window destructor.
     */
    ~MainWindow();

private:
    /**
     * @~russian
     * @brief Главное меню окна.
     *
     * @~english
     * @brief The main menu of the window.
     */
    QMenuBar *barMainMenu;

    /**
     * @~russian
     * @brief Меню «Файл».
     *
     * @~english
     * @brief The File menu.
     */
    QMenu *menuFile;

    /**
     * @~russian
     * @brief Меню «Справка».
     *
     * @~english
     * @brief The Help menu.
     */
    QMenu *menuHelp;

    /**
     * @~russian
     * @brief Панель инструментов.
     *
     * @~english
     * @brief The tools menu bar.
     */
    QToolBar *barTools;

    /**
     * @~russian
     * @brief Панель состояния.
     *
     * @~english
     * @brief The status bar.
     */
    QStatusBar *barStatus;

    /**
     * @~russian
     * @brief Действие «Открыть...» меню «Файл».
     *
     * @~english
     * @brief Open action.
     */
    QAction *actnFileOpen;

    /**
     * @~russian
     * @brief Действие «Добавить папку» меню «Файл».
     *
     * @~english
     * @brief Append Directory action.
     */
    QAction *actnFileAppendDir;

    /**
     * @~russian
     * @brief Действие «Добавить папку и все ее подпапки» меню «Файл».
     *
     * @~english
     * @brief Append Directory Recursively action.
     */
    QAction *actnFileAppendDirRecursively;

    /**
     * @~russian
     * @brief Действие «Выход» меню «Файл».
     *
     * @~english
     * @brief Exit action.
     */
    QAction *actnFileExit;

    /**
     * @~russian
     * @brief Действие «О программе» меню «Справка».
     *
     * @~english
     * @brief About action.
     */
    QAction *actnHelpAbout;

    /**
     * @~russian
     * @brief Действие «О Qt» меню «Справка».
     *
     * @~english
     * @brief About Qt action.
     */
    QAction *actnHelpAboutQt;

    /**
     * @~russian
     * @brief Разделитель главного окна.
     *
     * Обеспечивает изменение относительных размеров таблицы метаданных и журнала событий.
     *
     * @~english
     * @brief Main window splitter.
     *
     * Provides change the relative sizes of the table metadata and event log.
     */
    QSplitter *splMain;

    /**
     * @~russian
     * @brief Таблица метаданных.
     *
     * @~english
     * @brief Table of metadata.
     */
    QTableView *tblData;

    /**
     * @~russian
     * @brief Журнал событий.
     *
     * @~english
     * @brief Event log.
     */
    QTextEdit *edtLog;

    /**
     * @~russian
     * @brief Рабочая директория.
     *
     * Директория, указываемая при открытии диалогов добавления файлов и папок.
     *
     * @~english
     * @brief Working Directory.
     *
     * The directory specified for an open dialogue to add files and folders.
     */
    QString workingDir;

    /**
     * @~russian
     * @brief Модель данных, отображаемых в таблице.
     *
     * @~english
     * @brief Data model displayed in table.
     */
    TableModel *mdlData;

    /**
     * @~russian
     * @brief Соединение сигналов потока чтения со слотами обработки.
     * @param rd Указатель на поток чтения.
     *
     * @~english
     * @brief Connection of signals of reading thread with handler slots.
     * @param rd Pointer to reading thread.
     */
    void setReaderSigSlots(Reader *rd);
public slots:

    /**
     * @~russian
     * @brief Обработчик сообщений, направляемых в журнал событий.
     * @param msg Сообщение.
     *
     * @~english
     * @brief Message handler sent to the event log.
     * @param msg Message.
     */
    void onEventMessage(const QString &msg);

private slots:

    /**
     * @~russian
     * @brief Обработчик действия «Открыть...».
     *
     * @~english
     * @brief Open action handler.
     */
    void onFileOpen();

    /**
     * @~russian
     * @brief Обработчик действия «Добавить папку».
     *
     * @~english
     * @brief Append Directory action handler.
     */
    void onFileAppendDir();

    /**
     * @~russian
     * @brief Обработчик действия «Добавить папку и все ее подпапки».
     *
     * @~english
     * @brief Append Directory Recursively action handler.
     */
    void onFileAppendDirRecursively();

    /**
     * @~russian
     * @brief Обработчик действия «Выход».
     *
     * @~english
     * @brief Exit action handler.
     */
    void onFileExit();

    /**
     * @~russian
     * @brief Обработчик действия «О программе».
     *
     * @~english
     * @brief About action handler.
     */
    void onHelpAbout();

    /**
     * @~russian
     * @brief Обработчик действия «О Qt».
     *
     * @~english
     * @brief About Qt action handler.
     */
    void onHelpAboutQt();

};

#endif // MAINWINDOW_H
