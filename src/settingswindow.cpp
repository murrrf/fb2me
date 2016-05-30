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

    hlpRenameTemplates = new SettingsHelper();
    hlpRenameTemplates->setHelpString(tr("%F - author's first name; %M - author's middle name;<br/>"
                                         "%L - author's last name; %A - first letter of author's last name;<br/>"
                                         "%B - book title; %S - sequence name; %N - sequence number.<br/>"
                                         "Optional parameters are written in curly brackets."));

    hlpExternalEditors = new SettingsHelper();
    hlpExternalEditors->setHelpString(tr("%1 - name of book file substituted to command line"));

    tbMain = new QTabWidget();
    tbMain->addTab(hlpRenameTemplates, tr("Rename templates"));
    tbMain->addTab(hlpExternalEditors, tr("External Editors"));

    boxButtons = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    connect(boxButtons, SIGNAL(accepted()), this, SLOT(accept()));
    connect(boxButtons, SIGNAL(rejected()), this, SLOT(reject()));

    boxMain = new QVBoxLayout();
    boxMain->addWidget(tbMain);
    boxMain->addWidget(boxButtons);
    this->setLayout(boxMain);

    // Read settings from file
    QSettings settings(NAMES::nameDeveloper, NAMES::nameApplication);
    int size = settings.beginReadArray(NAMES::nameTemplateGroup);
    setting_t lstRenameTemplates;

    for (int i = 0; i < size; ++i)
    {
        settings.setArrayIndex(i);
        lstRenameTemplates.append(qMakePair(settings.value(NAMES::nameKey).toString(),
                                            settings.value(NAMES::nameValue).toString()));
    }

    hlpRenameTemplates->setSettingsList(lstRenameTemplates);
    settings.endArray();

    size = settings.beginReadArray(NAMES::nameExtEditorGroup);
    setting_t lstExtEditors;

    for (int i = 0; i < size; ++i)
    {
        settings.setArrayIndex(i);
        lstExtEditors.append(qMakePair(settings.value(NAMES::nameKey).toString(),
                                       settings.value(NAMES::nameValue).toString()));
    }

    hlpExternalEditors->setSettingsList(lstExtEditors);
    settings.endArray();
}

SettingsWindow::~SettingsWindow()
{
    delete hlpExternalEditors;
    delete hlpRenameTemplates;
    delete tbMain;
    delete boxButtons;
    delete boxMain;
}

setting_t SettingsWindow::getTemplatesList()
{
    return hlpRenameTemplates->getSettingsList();
}

setting_t SettingsWindow::getEditorsList()
{
    return hlpExternalEditors->getSettingsList();
}

void SettingsWindow::accept()
{
    QSettings settings(NAMES::nameDeveloper, NAMES::nameApplication);

    setting_t::iterator it;
    int cntIndex;

    settings.beginWriteArray(NAMES::nameTemplateGroup);
    setting_t lstRenameTemplates = hlpRenameTemplates->getSettingsList();
    cntIndex = 0;

    for (it = lstRenameTemplates.begin(); it != lstRenameTemplates.end(); ++it)
    {
        settings.setArrayIndex(cntIndex++);
        settings.setValue(NAMES::nameKey, (*it).first);
        settings.setValue(NAMES::nameValue, (*it).second);
    }

    settings.endArray();

    settings.beginWriteArray(NAMES::nameExtEditorGroup);
    setting_t lstExtEditors = hlpExternalEditors->getSettingsList();
    cntIndex = 0;

    for (it = lstExtEditors.begin(); it != lstExtEditors.end(); ++it)
    {
        settings.setArrayIndex(cntIndex++);
        settings.setValue(NAMES::nameKey, (*it).first);
        settings.setValue(NAMES::nameValue, (*it).second);
    }

    settings.endArray();

    QDialog::accept();
}
