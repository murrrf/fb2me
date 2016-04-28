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
class QTabWidget;

class TableModel;
class FileReader;

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
     * @brief The main window constructor.
     * @param parent Parent window pointer.
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
     * @brief Меню «Выбор».
     *
     * @~english
     * @brief The Select menu.
     */
    QMenu *menuSelect;

    /**
     * @~russian
     * @brief Меню «Инструменты».
     *
     * @~english
     * @brief The Tools menu.
     */
    QMenu *menuTools;

    /**
     * @~russian
     * @brief Подменю «Переместить и переименовать по шаблону» меню «Инструменты».
     *
     * @~english
     * @brief The submenu «Move and rename according to the template» of Tools menu.
     */
    QMenu *subToolsMoveTo;

    /**
     * @~russian
     * @brief Подменю «Копировать и переименовать по шаблону» меню «Инструменты».
     *
     * @~english
     * @brief The submenu «Copy and rename according to the template» of Tools menu.
     */
    QMenu *subToolsCopyTo;

    /**
     * @~russian
     * @brief Подменю «Переименовать на месте» меню «Инструменты».
     *
     * @~english
     * @brief The submenu «In-place rename» of Tools menu.
     */
    QMenu *subToolsInplaceRename;

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
     * @brief Действие «Очистить список файлов» меню «Файл».
     *
     * @~english
     * @brief Clear file list action.
     */
    QAction *actnFileClearFileList;

    /**
     * @~russian
     * @brief Действие «Очистить журнал» меню «Файл».
     *
     * @~english
     * @brief Clear log action.
     */
    QAction *actnFileClearLog;

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
     * @brief Действие «Отметить все файлы» меню «Выбор».
     *
     * @~english
     * @brief Select All Files action.
     */
    QAction *actnSelectAllFiles;

    /**
     * @~russian
     * @brief Действие «Отметить только архивы» меню «Выбор».
     *
     * @~english
     * @brief Select Compressed Files Only action.
     */
    QAction *actnSelectOnlyCompressed;

    /**
     * @~russian
     * @brief Действие «Обратить выделение» меню «Выбор».
     *
     * @~english
     * @brief Invert Selection action.
     */
    QAction *actnSelectInvertSelection;

    /**
     * @~russian
     * @brief Действие «Распаковать» меню «Инструменты».
     *
     * @~english
     * @brief Uncompress selected files action.
     */
    QAction *actnToolsUncompress;

    /**
     * @~russian
     * @brief Действие «Запаковать» меню «Инструменты».
     *
     * @~english
     * @brief Compress selected files action.
     */
    QAction *actnToolsCompress;

    /**
     * @~russian
     * @brief Действие «Настройки» меню «Инструменты».
     *
     * @~english
     * @brief Open settings window action.
     */
    QAction *actnToolsSettings;

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
     * @brief Переключатель закладок для панели информации.
     *
     * @~english
     * @brief Tab switcher for information panel.
     */
    QTabWidget *tabInfo;

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
    void setReaderSigSlots(FileReader *rd);

    /**
     * @~russian
     * @brief Создание подменю переименования файлов.
     * @param list Список шаблонов переименования.
     *
     * @~english
     * @brief Create submenu of rename files.
     * @param list List of renaming templates.
     */
    void addTemplatesListToMenu(const QStringList &list);

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

    /**
     * @~russian
     * @brief Обработчик сообщений об ошибках, направляемых в журнал событий.
     * @param msg Сообщение.
     *
     * @~english
     * @brief Error message handler sent to the event log.
     * @param msg Message.
     */
    void onErrorMessage(const QString &msg);

    /**
     * @~russian
     * @brief Обработчик начала длительной операции.
     *
     * Переключает курсор для наглядности.
     *
     * @~english
     * @brief Handler beginning of a lengthy operation.
     *
     * Switches mouse pointer for clarity.
     */
    void onBlockInput();

    /**
     * @~russian
     * @brief Обработчик окончания длительной операции.
     *
     * Переключает курсор для наглядности.
     *
     * @~english
     * @brief Handler end of a lengthy operation.
     *
     * Switches mouse pointer for clarity.
     */
    void onUnblockInput();

    /**
     * @~russian
     * @brief Обработчик установки количества выбранных записей в таблице.
     * @param count Количество выбранных файлов.
     *
     * @~english
     * @brief Handler of setting of selected files count.
     * @param count Number of selected files.
     */
    void onSetSelected(int count);

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
     * @brief Обработчик действия «Очистить список файлов».
     *
     * @~english
     * @brief Clear file list action handler.
     */
    void onFileClearFileList();

    /**
     * @~russian
     * @brief Обработчик действия «Очистить журнал».
     *
     * @~english
     * @brief Clear log action handler.
     */
    void onFileClearLog();

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
     * @brief Обработчик сигнала «Переместить и переименовать по шаблону» меню «Инструменты».
     *
     * @~english
     * @brief Handler for «Move and rename according to the template» action of Tools menu.
     */
    void onToolsMoveTo();

    /**
     * @~russian
     * @brief Обработчик сигнала «Копировать и переименовать по шаблону» меню «Инструменты».
     *
     * @~english
     * @brief Handler for «Copy and rename according to the template» action of Tools menu.
     */
    void onToolsCopyTo();

    /**
     * @~russian
     * @brief Обработчик сигнала «Переименовать на месте по шаблону» меню «Инструменты».
     *
     * @~english
     * @brief Handler for «In-place rename according to the template» action of Tools menu.
     */
    void onToolsInplaceRename();

    /**
     * @~russian
     * @brief Обработчик действия «Настройки».
     *
     * @~english
     * @brief Display settings dialog action handler.
     */
    void onToolsSettings();

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

    /**
     * @~russian
     * @brief Обработчик контекстного меню таблицы.
     * @param point Точка, в которой вызвано меню.
     *
     * @~english
     * @brief Table context menu handler.
     * @param point The point at which the menu is called.
     */
    void onTableContextMenuRequested(const QPoint &point);

    /**
     * @~russian
     * @brief Обработчик вызова диалога редактирования из контекстного меню.
     *
     * @~english
     * @brief Handler of the call Edit dialog from the context menu.
     */
    void onTableOpenEditor();

};

#endif // MAINWINDOW_H
