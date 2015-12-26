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

/*
 * @file
 * @~russian
 * @brief Файл реализации для главного окна программы.
 *
 * @~english
 * @brief Source file for main GUI window.
 */

#include "mainwindow.h"

#include "tablemodel.h"
#include "filereader.h"

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

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->resize(1024, 768);
    this->setWindowTitle(trUtf8("FB2 Metadata Editor"));

    // Panels setup

    barMainMenu = new QMenuBar();

    menuFile = new QMenu(trUtf8("File"), this);
    menuTools = new QMenu(trUtf8("Tools"), this);
    menuHelp = new QMenu(trUtf8("Help"), this);

    barMainMenu->addMenu(menuFile);
    barMainMenu->addMenu(menuTools);
    barMainMenu->addMenu(menuHelp);
    barMainMenu->show();
    barMainMenu->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    barTools = new QToolBar();
    barTools->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    barStatus = new QStatusBar();
    barStatus->setSizeGripEnabled(true);

    this->setMenuBar(barMainMenu);
    this->addToolBar(barTools);
    this->setStatusBar(barStatus);

    // Actions setup

    actnFileOpen = new QAction(QIcon::fromTheme("document-open", QIcon(":/img/document-open.png")),
                               trUtf8("Open file..."), this);
    connect(actnFileOpen, SIGNAL(triggered()), this, SLOT(onFileOpen()));
    menuFile->addAction(actnFileOpen);

    actnFileAppendDir = new QAction(QIcon::fromTheme("folder-open", QIcon(":/img/document-open-folder.png")),
                                    trUtf8("Append directory..."), this);
    connect(actnFileAppendDir, SIGNAL(triggered()), this, SLOT(onFileAppendDir()));
    menuFile->addAction(actnFileAppendDir);

    actnFileAppendDirRecursively = new QAction(QIcon::fromTheme("folder-open", QIcon(":/img/folder-open.png")),
            trUtf8("Append directory recursively..."), this);
    connect(actnFileAppendDirRecursively, SIGNAL(triggered()), this, SLOT(onFileAppendDirRecursively()));
    menuFile->addAction(actnFileAppendDirRecursively);

    menuFile->addSeparator();

    actnFileExit = new QAction(QIcon::fromTheme("application-exit", QIcon(":/img/application-exit.png")),
                               trUtf8("Exit"), this);
    connect(actnFileExit, SIGNAL(triggered()), this, SLOT(onFileExit()));
    menuFile->addAction(actnFileExit);

    actnToolsUncompress = new QAction(trUtf8("Uncompress"), this);
    actnToolsUncompress->setEnabled(false);
    menuTools->addAction(actnToolsUncompress);

    actnToolsCompress = new QAction(trUtf8("Compress"), this);
    actnToolsCompress->setEnabled(false);
    menuTools->addAction(actnToolsCompress);

    actnHelpAbout = new QAction(QIcon::fromTheme("help-about", QIcon(":/img/help-about.png")),
                                trUtf8("About"), this);
    connect(actnHelpAbout, SIGNAL(triggered()), this, SLOT(onHelpAbout()));
    menuHelp->addAction(actnHelpAbout);

    actnHelpAboutQt = new QAction(
#if (QT_VERSION >= QT_VERSION_CHECK(5,0,0))
        QIcon(":/qt-project.org/qmessagebox/images/qtlogo-64.png"),
#else
        QIcon(":/trolltech/qmessagebox/images/qtlogo-64.png"),
#endif
        trUtf8("About Qt"), this);
    connect(actnHelpAboutQt, SIGNAL(triggered()), this, SLOT(onHelpAboutQt()));
    menuHelp->addAction(actnHelpAboutQt);

    // TODO Add menus for all planned functions

    // Toolbar setup

    barTools->addAction(actnFileOpen);
    barTools->addAction(actnFileAppendDir);
    barTools->addAction(actnFileAppendDirRecursively);
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

    connect(mdlData, SIGNAL(EventMessage(QString)), this, SLOT(onEventMessage(QString)));
    connect(mdlData, SIGNAL(SetSelected(int)), this, SLOT(onSetSelected(int)));

    connect(actnToolsUncompress, SIGNAL(triggered()), mdlData, SLOT(onUnzipSelected()));
    connect(actnToolsCompress, SIGNAL(triggered()), mdlData, SLOT(onZipSelected()));

    tabInfo = new QTabWidget();
    splMain->addWidget(tabInfo);

    edtLog = new QTextEdit();
    edtLog->setReadOnly(true);
    tabInfo->addTab(edtLog, trUtf8("Message Log"));

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
    delete actnToolsCompress;
    delete actnToolsUncompress;
    delete actnFileExit;
    delete actnFileAppendDirRecursively;
    delete actnFileAppendDir;
    delete actnFileOpen;
    delete barStatus;
    delete barTools;
    delete menuHelp;
    delete menuTools;
    delete menuFile;
    delete barMainMenu;
}

void MainWindow::setReaderSigSlots(FileReader *rd)
{
    connect(rd, SIGNAL(started()), mdlData, SLOT(onBeginReading()));
    connect(rd, SIGNAL(started()), this, SLOT(onBlockInput()));
    connect(rd, SIGNAL(finished()), mdlData, SLOT(onEndReading()));
    connect(rd, SIGNAL(finished()), rd, SLOT(deleteLater()));
    connect(rd, SIGNAL(finished()), this, SLOT(onUnblockInput()));
    connect(rd, SIGNAL(AppendRecord(FileRecord)), mdlData, SLOT(onAppendRecord(FileRecord)));
    connect(rd, SIGNAL(EventMessage(QString)), this, SLOT(onEventMessage(QString)));

    rd->start();
}

void MainWindow::onEventMessage(const QString &msg)
{
    edtLog->append(QString("%1: %2").arg(QDateTime::currentDateTime().toString("hh:mm:ss:zzz"), msg));
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

void MainWindow::onSetSelected(int count)
{
    if (count > 0)
    {
        actnToolsUncompress->setEnabled(true);
        actnToolsCompress->setEnabled(true);
    }
    else
    {
        actnToolsUncompress->setEnabled(false);
        actnToolsCompress->setEnabled(false);
    }
}

void MainWindow::onFileOpen()
{
    QStringList filenames = QFileDialog::getOpenFileNames(this, trUtf8("Open file"), workingDir,
                            trUtf8("Fictionbook files(*.fb2 *.fb2.zip)"));

    FileReader *reader = new FileReader(filenames);
    setReaderSigSlots(reader);
}

void MainWindow::onFileAppendDir()
{
    QString dir = QFileDialog::getExistingDirectory(this, trUtf8("Append Directory"), workingDir,
                  QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    FileReader *reader = new FileReader(dir, false);
    setReaderSigSlots(reader);
}

void MainWindow::onFileAppendDirRecursively()
{
    QString dir = QFileDialog::getExistingDirectory(this, trUtf8("Append Directory"), workingDir,
                  QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    FileReader *reader = new FileReader(dir, true);
    setReaderSigSlots(reader);
}

void MainWindow::onFileExit()
{
    close();
}

void MainWindow::onHelpAbout()
{
    QString caption = trUtf8("About FB2ME");

    QString header = "<p align='center'>"
                     "<big><b>%1</b></big><br/>"
                     "%2 %3<br/>"
                     "%4"
                     "</p>";

    QString record = "<p>%1<br/><small>%2</small></p>";

    QString message = header.arg(trUtf8("FB2 Metadata Editor"),
                                 trUtf8("Version"), QApplication::applicationVersion(),
                                 trUtf8("A metadata editor for FictionBook files"));
    message += record.arg(
                   trUtf8("Copyright &copy; %1 Veter").arg("2015"),
                   trUtf8("Released under the <a href=%1>GPL 3</a> license").arg("\"http://www.gnu.org/licenses/gpl.html\""));
    message += record.arg(
                   trUtf8("Fallback icons from the <a href=%1>Oxygen</a> icon theme").arg("\"https://techbase.kde.org/Projects/Oxygen\""),
                   trUtf8("Used under the <a href=%1>LGPL 3</a> license").arg("\"http://www.gnu.org/licenses/lgpl.html\""));
    message += record.arg(
                   trUtf8("ZIP archive support from <a href=%1>miniz.c</a> library").arg("\"https://code.google.com/p/miniz\""),
                   trUtf8("Released as <a href=%1>public domain</a>").arg("\"http://unlicense.org\""));

    QMessageBox::about(this, caption, message);
}

void MainWindow::onHelpAboutQt()
{
    QMessageBox::aboutQt(this);
}
