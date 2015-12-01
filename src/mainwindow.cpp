#include "mainwindow.h"

/**
 * @file
 * @~russian
 * @brief Файл реализации для главного окна программы.
 *
 * @~english
 * @brief Source file for main GUI window.
 */

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

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->resize(1024, 768);
    this->setWindowTitle(trUtf8("FB2 Metadata Editor"));

    // Panels setup

    barMainMenu = new QMenuBar();

    menuFile = new QMenu(trUtf8("File"), this);
    menuHelp = new QMenu(trUtf8("Help"), this);

    barMainMenu->addMenu(menuFile);
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

    actnFileOpen = new QAction(QIcon::fromTheme("document-open", QIcon(":/img/document-open-folder.png")),
                               trUtf8("Open folder..."), this);
    connect(actnFileOpen, SIGNAL(triggered()), this, SLOT(onFileOpen()));
    menuFile->addAction(actnFileOpen);

    actnFileExit = new QAction(QIcon::fromTheme("application-exit", QIcon(":/img/application-exit.png")),
                               trUtf8("Exit"), this);
    connect(actnFileExit, SIGNAL(triggered()), this, SLOT(onFileExit()));
    menuFile->addAction(actnFileExit);

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

    // Toolbar setup

    barTools->addAction(actnHelpAbout);

    // Central widget setup

    splMain = new QSplitter(Qt::Vertical);

    tblMain = new QTableView();
    splMain->addWidget(tblMain);

    edtLog = new QTextEdit();
    edtLog->setReadOnly(true);
    splMain->addWidget(edtLog);

    this->setCentralWidget(splMain);
}

MainWindow::~MainWindow()
{
    delete edtLog;
    delete tblMain;
    delete splMain;
    delete actnHelpAboutQt;
    delete actnHelpAbout;
    delete actnFileExit;
    delete actnFileOpen;
    delete barStatus;
    delete barTools;
    delete menuHelp;
    delete menuFile;
    delete barMainMenu;
}

void MainWindow::onFileOpen()
{

}

void MainWindow::onFileExit()
{
    close();
}

void MainWindow::onHelpAbout()
{
    QMessageBox::about(this, trUtf8("About FB2ME"), QString(
                           "<p align='center'><big><b>%1</b></big><br/>%2 %3<br/>%4</p>"
                           "<p align='center'>%5<br/><small>%6</small></p>"
                           "<p align='center'>%7<br/><small>%8</small></p>").arg(
                           trUtf8("FB2 Metadata Editor"),
                           trUtf8("Version"), QApplication::applicationVersion(),
                           trUtf8("A metadata editor for fb2 files"),
                           trUtf8("Copyright &copy; %1 Veter").arg("2015"),
                           trUtf8("Released under the <a href= %1>GPL 3</a> license").arg("\"http://www.gnu.org/licenses/gpl.html\""),
                           trUtf8("Fallback icons from the Oxygen icon theme"),
                           trUtf8("Used under the <a href=%1>LGPL 3</a> license").arg("\"http://www.gnu.org/licenses/lgpl.html\""))
                      );

}

void MainWindow::onHelpAboutQt()
{
    QMessageBox::aboutQt(this);
}
