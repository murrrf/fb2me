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

#include "settingswindow.h"
#include "consts.h"

#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QLabel>
#include <QListWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QInputDialog>
#include <QMessageBox>
#include <QSettings>
#include <QTabWidget>

SettingsWindow::SettingsWindow(QWidget *parent)
    : QDialog(parent)
{
    // Set up UI

    hlpRenameTemplates = new SettingsHelper(tr("Rename templates"));
    hlpRenameTemplates->setHelpString(tr("%F - author's first name; %M - author's middle name;<br/>"
                                  "%L - author's last name; %A - first letter of author's last name;<br/>"
                                  "%B - book title; %S - sequence name; %N - sequence number.<br/>"
                                  "Optional parameters are written in curly brackets."));
    boxButtons = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    connect(boxButtons, SIGNAL(accepted()), this, SLOT(accept()));
    connect(boxButtons, SIGNAL(rejected()), this, SLOT(reject()));

    tbMain = new QTabWidget();
    tbMain->addTab(hlpRenameTemplates,tr("Rename"));

    boxMain = new QVBoxLayout();
    boxMain->addWidget(tbMain);
    boxMain->addWidget(boxButtons);
    this->setLayout(boxMain);

    // Read settings from file
    QSettings settings(NAMES::nameDeveloper, NAMES::nameApplication);
    int size = settings.beginReadArray(NAMES::nameTemplateGroup);
    setting_t list;

    for (int i = 0; i < size; ++i)
    {
        settings.setArrayIndex(i);
        list.append(qMakePair(settings.value(NAMES::nameKey).toString(), settings.value(NAMES::nameValue).toString()));
    }

    hlpRenameTemplates->setSettingsList(list);
    settings.endArray();
}

SettingsWindow::~SettingsWindow()
{
    delete hlpRenameTemplates;
    delete tbMain;
    delete boxButtons;
    delete boxMain;
}

setting_t SettingsWindow::getTemplatesList()
{
    return hlpRenameTemplates->getSettingsList();
}

void SettingsWindow::accept()
{
    QSettings settings(NAMES::nameDeveloper, NAMES::nameApplication);
    settings.beginWriteArray(NAMES::nameTemplateGroup);

    setting_t list = hlpRenameTemplates->getSettingsList();

    setting_t::iterator it;
    int cntIndex = 0;

    for (it = list.begin(); it != list.end(); ++it)
    {
        settings.setArrayIndex(cntIndex++);
        settings.setValue(NAMES::nameKey, (*it).first);
        settings.setValue(NAMES::nameValue, (*it).second);
    }

    settings.endArray();

    QDialog::accept();
}
