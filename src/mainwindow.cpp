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

/*
 * @file
 * @~russian
 * @brief Файл реализации для главного окна программы.
 *
 * @~english
 * @brief Source file for main GUI window.
 */

// TODO Realize edit of XML files (main task of application...)

#include "mainwindow.h"

#include "tablemodel.h"
#include "filereader.h"
#include "settingswindow.h"
#include "recordeditor.h"
#include "consts.h"

#include <QWidget>
#include <QVBoxLayout>
#include <QMenuBar>
#include <QToolBar>
#include <QStatusBar>
#include <QAction>
#include <QMessageBox>
#include <QTableView>
#include <QSplitter>
#include <QTextEdit>
#include <QApplication>
#include <QFileDialog>
#include <QStandardPaths>
#include <QDateTime>
#include <QTabWidget>
#include <QDialog>
#include <QSettings>
#include <QProcess>
#include <QLabel>
#include <QDebug>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->resize(1024, 768);
    this->setWindowTitle(tr("FB2 Metadata Editor"));

    // Panels setup

    barMainMenu = new QMenuBar();

    menuFile = new QMenu(tr("File"), this);
    menuSelect = new QMenu(tr("Select"), this);
    menuTools = new QMenu(tr("Tools"), this);
    menuHelp = new QMenu(tr("Help"), this);

    barMainMenu->addMenu(menuFile);
    barMainMenu->addMenu(menuSelect);
    barMainMenu->addMenu(menuTools);
    barMainMenu->addMenu(menuHelp);
    barMainMenu->show();
    barMainMenu->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    barTools = new QToolBar();
    barTools->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    barStatus = new QStatusBar();
    barStatus->setSizeGripEnabled(true);

    statusCounter = new QLabel();
    barStatus->addPermanentWidget(statusCounter);

    tmrLoadTime = new QTime();
    cntPreviousLoaded = 0;

    this->setMenuBar(barMainMenu);
    this->addToolBar(barTools);
    this->setStatusBar(barStatus);

    // Actions setup

    // Setup Files menu

    actnFileOpen = new QAction(QIcon::fromTheme("document-open", QIcon(":/img/document-open.png")),
                               tr("Open file..."), this);
    connect(actnFileOpen, SIGNAL(triggered()), this, SLOT(onFileOpen()));
    menuFile->addAction(actnFileOpen);

    actnFileAppendDir = new QAction(QIcon::fromTheme("folder-open", QIcon(":/img/document-open-folder.png")),
                                    tr("Append directory..."), this);
    connect(actnFileAppendDir, SIGNAL(triggered()), this, SLOT(onFileAppendDir()));
    menuFile->addAction(actnFileAppendDir);

    actnFileAppendDirRecursively = new QAction(QIcon::fromTheme("folder-open", QIcon(":/img/folder-open.png")),
            tr("Append directory recursively..."), this);
    connect(actnFileAppendDirRecursively, SIGNAL(triggered()), this, SLOT(onFileAppendDirRecursively()));
    menuFile->addAction(actnFileAppendDirRecursively);

    menuFile->addSeparator();

    actnFileClearFileList = new QAction(tr("Clear list of files"), this);
    connect(actnFileClearFileList, SIGNAL(triggered()), this, SLOT(onFileClearFileList()));
    menuFile->addAction(actnFileClearFileList);

    actnFileClearLog = new QAction(tr("Clear log"), this);
    connect(actnFileClearLog, SIGNAL(triggered()), this, SLOT(onFileClearLog()));
    menuFile->addAction(actnFileClearLog);

    actnFileClearFileListLog = new QAction(tr("Clear list of files and log"), this);
    connect(actnFileClearFileListLog, SIGNAL(triggered()), this, SLOT(onFileClearFileListLog()));
    menuFile->addAction(actnFileClearFileListLog);

    menuFile->addSeparator();

    actnFileExit = new QAction(QIcon::fromTheme("application-exit", QIcon(":/img/application-exit.png")),
                               tr("Exit"), this);
    connect(actnFileExit, SIGNAL(triggered()), this, SLOT(onFileExit()));
    menuFile->addAction(actnFileExit);

    // Setup Select menu

    actnSelectAllFiles = new QAction(tr("Select all"), this);
    menuSelect->addAction(actnSelectAllFiles);

    actnSelectOnlyCompressed = new QAction(tr("Select compressed files only"), this);
    menuSelect->addAction(actnSelectOnlyCompressed);

    actnSelectInvertSelection = new QAction(tr("Invert selection"), this);
    menuSelect->addAction(actnSelectInvertSelection);

    // Setup Tools menu

    actnToolsUncompress = new QAction(tr("Uncompress"), this);
    actnToolsUncompress->setEnabled(false);
    menuTools->addAction(actnToolsUncompress);

    actnToolsCompress = new QAction(tr("Compress"), this);
    actnToolsCompress->setEnabled(false);
    menuTools->addAction(actnToolsCompress);

    subToolsMoveTo = new QMenu(tr("Move to"), this);
    menuTools->addMenu(subToolsMoveTo);
    subToolsCopyTo = new QMenu(tr("Copy to"), this);
    menuTools->addMenu(subToolsCopyTo);
    subToolsInplaceRename = new QMenu(tr("In-place rename"), this);
    menuTools->addMenu(subToolsInplaceRename);

    menuTools->addSeparator();

    actnToolsSettings = new QAction(QIcon::fromTheme("preferences-system", QIcon(":/img/preferences-system.png")),
                                    tr("Settings..."), this);
    connect(actnToolsSettings, SIGNAL(triggered()), this, SLOT(onToolsSettings()));
    menuTools->addAction(actnToolsSettings);

    QSettings settings(NAMES::nameDeveloper, NAMES::nameApplication);
    int size = settings.beginReadArray(NAMES::nameTemplateGroup);
    setting_t templates;

    for (int i = 0; i < size; ++i)
    {
        settings.setArrayIndex(i);
        templates.append(qMakePair(settings.value(NAMES::nameKey).toString(), settings.value(NAMES::nameValue).toString()));
    }

    settings.endArray();

    size = settings.beginReadArray(NAMES::nameExtEditorGroup);

    for (int i = 0; i < size; ++i)
    {
        settings.setArrayIndex(i);
        extEditors.append(qMakePair(settings.value(NAMES::nameKey).toString(), settings.value(NAMES::nameValue).toString()));
    }

    settings.endArray();

    // Setup Help menu

    actnHelpAbout = new QAction(QIcon::fromTheme("help-about", QIcon(":/img/help-about.png")),
                                tr("About..."), this);
    connect(actnHelpAbout, SIGNAL(triggered()), this, SLOT(onHelpAbout()));
    menuHelp->addAction(actnHelpAbout);

    actnHelpAboutQt = new QAction(
#if (QT_VERSION >= QT_VERSION_CHECK(5,0,0))
        QIcon(":/qt-project.org/qmessagebox/images/qtlogo-64.png"),
#else
        QIcon(":/trolltech/qmessagebox/images/qtlogo-64.png"),
#endif
        tr("About Qt..."), this);
    connect(actnHelpAboutQt, SIGNAL(triggered()), this, SLOT(onHelpAboutQt()));
    menuHelp->addAction(actnHelpAboutQt);

    // TODO Add menus for all planned functions

    // Toolbar setup

    barTools->addAction(actnFileOpen);
    barTools->addAction(actnFileAppendDir);
    barTools->addAction(actnFileAppendDirRecursively);
    barTools->addSeparator();
    barTools->addAction(actnToolsSettings);
    barTools->addSeparator();
    barTools->addAction(actnHelpAbout);

    // Central widget setup

    splMain = new QSplitter(Qt::Vertical);
    splMain->setChildrenCollapsible(false);

    tblData = new QTableView();
    splMain->addWidget(tblData);

    mdlData = new TableModel(this);
    tblData->setModel(mdlData);
    tblData->resizeColumnToContents(colCheckColumn);

    addTemplatesListToMenu(templates);

    connect(mdlData, SIGNAL(EventMessage(QString)), this, SLOT(onEventMessage(QString)));
    connect(mdlData, SIGNAL(ErrorMessage(QString)), this, SLOT(onErrorMessage(QString)));
    connect(mdlData, SIGNAL(SetSelected(int)), this, SLOT(onSetSelected(int)));

    connect(actnToolsUncompress, SIGNAL(triggered()), mdlData, SLOT(onUnzipSelected()));
    connect(actnToolsCompress, SIGNAL(triggered()), mdlData, SLOT(onZipSelected()));

    connect(actnSelectAllFiles, SIGNAL(triggered()), mdlData, SLOT(onSelectAll()));
    connect(actnSelectInvertSelection, SIGNAL(triggered()), mdlData, SLOT(onInvertSelection()));

    tblData->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(tblData, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(onTableContextMenuRequested(QPoint)));
    tblData->setSelectionBehavior(QAbstractItemView::SelectRows);

    tabInfo = new QTabWidget();
    splMain->addWidget(tabInfo);

    edtLog = new QTextEdit();
    edtLog->setReadOnly(true);
    tabInfo->addTab(edtLog, tr("Message Log"));

    // TODO Add context menu for Message Log

    splMain->setStretchFactor(0, 1); // First widget must be wide than second

    this->setCentralWidget(splMain);

    // Additional settings
#if defined Q_OS_UNIX
    QStringList homedir = QStandardPaths::standardLocations(QStandardPaths::HomeLocation);
#elif defined Q_OS_WINDOWS
    QStringList homedir = QStandardPaths::standardLocations(QStandardPaths::DocumentsLocation);
#endif
    workingDir = homedir.at(0);

    qRegisterMetaType<FileRecord>("FileRecord");
}

MainWindow::~MainWindow()
{
    delete edtLog;
    delete tabInfo;
    delete mdlData;
    delete tblData;
    delete splMain;
    delete actnHelpAboutQt;
    delete actnHelpAbout;
    subToolsInplaceRename->clear();
    delete subToolsInplaceRename;
    subToolsCopyTo->clear();
    delete subToolsCopyTo;
    subToolsMoveTo->clear();
    delete subToolsMoveTo;
    delete actnToolsSettings;
    delete actnToolsCompress;
    delete actnToolsUncompress;
    delete actnFileExit;
    delete actnSelectInvertSelection;
    delete actnSelectOnlyCompressed;
    delete actnSelectAllFiles;
    delete actnFileClearFileListLog;
    delete actnFileClearLog;
    delete actnFileClearFileList;
    delete actnFileAppendDirRecursively;
    delete actnFileAppendDir;
    delete actnFileOpen;
    delete statusCounter;
    delete tmrLoadTime;
    delete barStatus;
    delete barTools;
    delete menuHelp;
    delete menuTools;
    delete menuSelect;
    delete menuFile;
    delete barMainMenu;
}

void MainWindow::setReaderSigSlots(FileReader *rd)
{
    connect(rd, SIGNAL(started()), mdlData, SLOT(onBeginReading()));
    connect(rd, SIGNAL(started()), this, SLOT(onBlockInput()));
    connect(rd, SIGNAL(started()), this, SLOT(onBeginReading()));
    connect(rd, SIGNAL(finished()), rd, SLOT(deleteLater()));
    connect(rd, SIGNAL(finished()), mdlData, SLOT(onEndReading()));
    connect(rd, SIGNAL(finished()), this, SLOT(onUnblockInput()));
    connect(rd, SIGNAL(finished()), this, SLOT(onEndReading()));
    connect(rd, SIGNAL(AppendRecord(FileRecord)), mdlData, SLOT(onAppendRecord(FileRecord)));
    connect(rd, SIGNAL(EventMessage(QString)), this, SLOT(onEventMessage(QString)));
    connect(rd, SIGNAL(ErrorMessage(QString)), this, SLOT(onErrorMessage(QString)));

    rd->start();
}

void MainWindow::addTemplatesListToMenu(const setting_t &list)
{
    subToolsMoveTo->clear();
    subToolsCopyTo->clear();
    subToolsInplaceRename->clear();

    setting_t::const_iterator it;
    QString key, value;

    for (it = list.begin(); it != list.end(); ++it)
    {
        key = (*it).first;
        value = (*it).second;

        QAction *move = new QAction(key, this);
        move->setToolTip(value);
        move->setProperty("template", value);
        move->setEnabled(false);
        connect(move, SIGNAL(triggered()), this, SLOT(onToolsMoveTo()));
        subToolsMoveTo->addAction(move);

        QAction *copy = new QAction(key, this);
        copy->setToolTip(value);
        copy->setProperty("template", value);
        copy->setEnabled(false);
        connect(copy, SIGNAL(triggered()), this, SLOT(onToolsCopyTo()));
        subToolsCopyTo->addAction(copy);

        QAction *rename = new QAction(key, this);
        rename->setToolTip(value);
        rename->setProperty("template", value);
        rename->setEnabled(false);
        connect(rename, SIGNAL(triggered()), this, SLOT(onToolsInplaceRename()));
        subToolsInplaceRename->addAction(rename);
    }

    onSetSelected(mdlData->getSelectedRecordsCount());
}

void MainWindow::setStatusBarCounter(int selected, int total)
{
    statusCounter->setText(QString::number(selected) + "/" + QString::number(total));
}

void MainWindow::onEventMessage(const QString &msg)
{
    edtLog->append(QString("%1: %2").arg(QDateTime::currentDateTime().toString("hh:mm:ss:zzz"), msg));
}

void MainWindow::onErrorMessage(const QString &msg)
{
    edtLog->append(QString("%1: <font color=red>%2</font>").arg(QDateTime::currentDateTime().toString("hh:mm:ss:zzz"),
                   msg));
}

void MainWindow::onBlockInput()
{
    QApplication::setOverrideCursor(Qt::BusyCursor);
    QApplication::processEvents();
}

void MainWindow::onUnblockInput()
{
    QApplication::restoreOverrideCursor();
}

void MainWindow::onBeginReading()
{
    tmrLoadTime->start();
}

void MainWindow::onEndReading()
{
    onSetSelected(mdlData->getSelectedRecordsCount());
    int count = mdlData->getRecordsCount() - cntPreviousLoaded;
    int sec = tmrLoadTime->elapsed() / 1000;
    barStatus->showMessage(tr("%1 files loaded in %2 seconds").arg(QString::number(count), QString::number(sec)), 5000);
    cntPreviousLoaded = mdlData->getRecordsCount();
}

void MainWindow::onSetSelected(int count)
{
    if (count > 0)
    {
        actnToolsUncompress->setEnabled(true);
        actnToolsCompress->setEnabled(true);

        QList<QAction *>::iterator it;

        for (it = subToolsMoveTo->actions().begin(); it < subToolsMoveTo->actions().end(); ++it)
        {
            (*it)->setEnabled(true);
        }

        for (it = subToolsCopyTo->actions().begin(); it < subToolsCopyTo->actions().end(); ++it)
        {
            (*it)->setEnabled(true);
        }

        for (it = subToolsInplaceRename->actions().begin(); it < subToolsInplaceRename->actions().end(); ++it)
        {
            (*it)->setEnabled(true);
        }
    }
    else
    {
        actnToolsUncompress->setEnabled(false);
        actnToolsCompress->setEnabled(false);

        QList<QAction *>::iterator it;

        for (it = subToolsMoveTo->actions().begin(); it < subToolsMoveTo->actions().end(); ++it)
        {
            (*it)->setEnabled(false);
        }

        for (it = subToolsCopyTo->actions().begin(); it < subToolsCopyTo->actions().end(); ++it)
        {
            (*it)->setEnabled(false);
        }

        for (it = subToolsInplaceRename->actions().begin(); it < subToolsInplaceRename->actions().end(); ++it)
        {
            (*it)->setEnabled(false);
        }
    }

    setStatusBarCounter(count, mdlData->getRecordsCount());
}

void MainWindow::onFileOpen()
{
    QStringList filenames = QFileDialog::getOpenFileNames(this, tr("Open file"), workingDir,
                            tr("Fictionbook files(*.fb2 *.fb2.zip)"));

    if (!filenames.isEmpty())
    {
        FileReader *reader = new FileReader(filenames);
        setReaderSigSlots(reader);
    }
}

void MainWindow::onFileAppendDir()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Append Directory"), workingDir,
                  QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

    if (!dir.isEmpty())
    {
        FileReader *reader = new FileReader(dir, false);
        setReaderSigSlots(reader);
    }
}

void MainWindow::onFileAppendDirRecursively()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Append Directory"), workingDir,
                  QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

    if (!dir.isEmpty())
    {
        FileReader *reader = new FileReader(dir, true);
        setReaderSigSlots(reader);
    }
}

void MainWindow::onFileClearFileList()
{
    emit mdlData->onClearList();
    cntPreviousLoaded = 0;
}

void MainWindow::onFileClearFileListLog()
{
    onFileClearFileList();
    onFileClearLog();
}

void MainWindow::onFileClearLog()
{
    edtLog->clear();
}

void MainWindow::onFileExit()
{
    close();
}

void MainWindow::onToolsMoveTo()
{
    QString basedir = QFileDialog::getExistingDirectory(this, tr("Move files to folder"), workingDir,
                      QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

    if (!basedir.isEmpty())
    {
        QString pattern = sender()->property("template").toString();
        emit mdlData->MoveTo(basedir, pattern);
    }
}

void MainWindow::onToolsCopyTo()
{
    QString basedir = QFileDialog::getExistingDirectory(this, tr("Copy files to folder"), workingDir,
                      QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

    if (!basedir.isEmpty())
    {
        QString pattern = sender()->property("template").toString();
        emit mdlData->CopyTo(basedir, pattern);
    }
}

void MainWindow::onToolsInplaceRename()
{
    //TODO This function not working properly. It should rename the file in-place, and not move it to subdirectory.
    QString basedir = QString();
    QString pattern = sender()->property("template").toString();
    emit mdlData->InplaceRename(basedir, pattern);
}

void MainWindow::onToolsExternalEditor()
{
    QString command = sender()->property("command").toString();

    if (command.indexOf("%1") != -1)
    {
        QString filename = mdlData->getRecord(sender()->property("index").toModelIndex()).getFileName();
        command = command.arg("\"" + filename + "\"");
        QProcess process;
        process.start(command);
        process.waitForFinished(-1);
    }
}

void MainWindow::onToolsSettings()
{
    SettingsWindow *settings = new SettingsWindow();

    if (settings->exec() == QDialog::Accepted)
    {
        addTemplatesListToMenu(settings->getTemplatesList());
        extEditors = settings->getEditorsList();
    }

    delete settings;
}

void MainWindow::onHelpAbout()
{
    QString caption = tr("About FB2ME");

    QString header = "<p align='center'>"
                     "<big><b>%1</b></big><br/>"
                     "%2 %3<br/>"
                     "%4"
                     "</p>";

    QString record = "<p>%1<br/><small>%2</small></p>";

    QString message = header.arg(tr("FB2 Metadata Editor"),
                                 tr("Version"), QApplication::applicationVersion(),
                                 tr("A metadata editor for FictionBook files"));
    message += record.arg(
                   tr("Copyright &copy; %1 Veter").arg("2015, 2016"),
                   tr("Released under the <a href=%1>GPL 3</a> license").arg("\"http://www.gnu.org/licenses/gpl.html\""));
    message += record.arg(
                   tr("Fallback icons from the <a href=%1>Oxygen</a> icon theme").arg("\"https://techbase.kde.org/Projects/Oxygen\""),
                   tr("Used under the <a href=%1>LGPL 3</a> license").arg("\"http://www.gnu.org/licenses/lgpl.html\""));
    message += record.arg(
                   tr("ZIP archive support from <a href=%1>miniz.c</a> library").arg("\"https://github.com/richgel999/miniz\""),
                   tr("Released as <a href=%1>public domain</a>").arg("\"http://unlicense.org\""));

    QMessageBox::about(this, caption, message);
}

void MainWindow::onHelpAboutQt()
{
    QMessageBox::aboutQt(this);
}

void MainWindow::onTableContextMenuRequested(const QPoint &point)
{
    QModelIndex ind = tblData->indexAt(point);

    if (!ind.isValid())
        return;

    QMenu *menu = new QMenu(this);

    QAction *edit = new QAction(tr("Edit metadata"), this);
    menu->addAction(edit);
    edit->setProperty("index", QVariant(ind));
    connect(edit, SIGNAL(triggered()), this, SLOT(onTableOpenEditor()));

    QAction *uncompress = new QAction(tr("Uncompress"), this);
    menu->addAction(uncompress);
    uncompress->setProperty("index", QVariant(ind));
    connect(uncompress, SIGNAL(triggered()), mdlData, SLOT(onUnzipCurrent()));

    QAction *compress = new QAction(tr("Compress"), this);
    menu->addAction(compress);
    compress->setProperty("index", QVariant(ind));
    connect(compress, SIGNAL(triggered()), mdlData, SLOT(onZipCurrent()));

    QMenu *subExtEditors = new QMenu(tr("External editors"), this);

    setting_t::const_iterator it;
    QString key, value;

    for (it = extEditors.begin(); it != extEditors.end(); ++it)
    {
        key = (*it).first;
        value = (*it).second;

        QAction *editor = new QAction(key, this);
        editor->setToolTip(value);
        editor->setProperty("index", QVariant(ind));
        editor->setProperty("command", value);
        connect(editor, SIGNAL(triggered()), this, SLOT(onToolsExternalEditor()));
        subExtEditors->addAction(editor);
    }

    menu->addMenu(subExtEditors);

    tblData->selectRow(ind.row());
    menu->popup(tblData->viewport()->mapToGlobal(point));

    // TODO Improve context menu
}

void MainWindow::onTableOpenEditor()
{
    QModelIndex index = sender()->property("index").toModelIndex();
    FileRecord record = mdlData->getRecord(index);

    RecordEditor *editor = new RecordEditor(&record);

    if (editor->exec() == QDialog::Accepted)
    {
    }

    delete editor;
}
