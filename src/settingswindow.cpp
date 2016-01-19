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

SettingsWindow::SettingsWindow(QWidget *parent)
    : QDialog(parent)
{
    // Set up UI

    QGroupBox *gbxPatterns = new QGroupBox(trUtf8("Rename templates"));
    QLabel *lblPatternsHelp = new QLabel(trUtf8("Help"));
    lstPatterns = new QListWidget();
    QPushButton *btnPatternAdd = new QPushButton(trUtf8("Add"));
    connect(btnPatternAdd, SIGNAL(clicked()), this, SLOT(onPatternAdd()));
    QPushButton *btnPatternEdit = new QPushButton(trUtf8("Edit"));
    connect(btnPatternEdit, SIGNAL(clicked()), this, SLOT(onPatternEdit()));
    QPushButton *btnPatternDelete = new QPushButton(trUtf8("Delete"));
    connect(btnPatternDelete, SIGNAL(clicked()), this, SLOT(onPatternDelete()));
    QHBoxLayout *boxPatternsButtons = new QHBoxLayout();
    boxPatternsButtons->addWidget(btnPatternAdd);
    boxPatternsButtons->addWidget(btnPatternEdit);
    boxPatternsButtons->addWidget(btnPatternDelete);
    QVBoxLayout *boxPatterns = new QVBoxLayout();
    boxPatterns->addWidget(lblPatternsHelp);
    boxPatterns->addWidget(lstPatterns);
    boxPatterns->addLayout(boxPatternsButtons);
    gbxPatterns->setLayout(boxPatterns);

    boxButtons = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    connect(boxButtons, SIGNAL(accepted()), this, SLOT(accept()));
    connect(boxButtons, SIGNAL(rejected()), this, SLOT(reject()));

    boxMain = new QVBoxLayout();
    boxMain->addWidget(gbxPatterns);
    boxMain->addWidget(boxButtons);
    this->setLayout(boxMain);

    // Read settings from file
    QSettings settings(NAMES::nameDeveloper, NAMES::nameApplication);
    int size = settings.beginReadArray(NAMES::nameTemplateGroup);

    for (int i = 0; i < size; i++)
    {
        settings.setArrayIndex(i);
        lstPatterns->addItem(settings.value(NAMES::nameTemplate).toString());
    }
}

SettingsWindow::~SettingsWindow()
{
    delete boxButtons;
    delete boxMain;
}

void SettingsWindow::accept()
{
    QSettings settings(NAMES::nameDeveloper, NAMES::nameApplication);
    settings.beginWriteArray(NAMES::nameTemplateGroup);

    for (int i = 0; i < lstPatterns->count(); i++)
    {
        settings.setArrayIndex(i);
        settings.setValue(NAMES::nameTemplate, lstPatterns->item(i)->text());
    }

    settings.endArray();

    QDialog::accept();
}

void SettingsWindow::onPatternAdd()
{
    bool ok;
    QString text = QInputDialog::getText(this, trUtf8("Add new template"), trUtf8("Enter template"), QLineEdit::Normal,
                                         "", &ok).trimmed();

    if (ok && !text.isEmpty())
    {
        QList<QListWidgetItem *> found = lstPatterns->findItems(text, Qt::MatchExactly);

        if (found.size() == 0)
        {
            lstPatterns->addItem(text);
        }
        else
        {
            if (QMessageBox::question(this, trUtf8("The template already exists"),
                                      trUtf8("The template \"%1\" already exists. Do you want to add it again?").arg(text),
                                      QMessageBox::Ok | QMessageBox::Cancel) == QMessageBox::Ok)
            {
                lstPatterns->addItem(text);
            }
        }
    }
}

void SettingsWindow::onPatternEdit()
{
    if (lstPatterns->currentRow() > -1)
    {
        bool ok;
        QString text = QInputDialog::getText(this, trUtf8("Edit template"), trUtf8("Enter template"), QLineEdit::Normal,
                                             lstPatterns->item(lstPatterns->currentRow())->text(), &ok).trimmed();

        if (ok && !text.isEmpty())
        {
            if (text != lstPatterns->item(lstPatterns->currentRow())->text())
            {
                lstPatterns->insertItem(lstPatterns->currentRow(), text);
                delete lstPatterns->takeItem(lstPatterns->currentRow());
                lstPatterns->setCurrentRow(lstPatterns->currentRow() - 1);
            }
        }
    }
}

void SettingsWindow::onPatternDelete()
{
    if (lstPatterns->currentRow() > -1)
    {
        if (QMessageBox::question(this, trUtf8("Delete template"),
                                  trUtf8("Delete template \"%1\"?").arg(lstPatterns->item(lstPatterns->currentRow())->text()),
                                  QMessageBox::Ok | QMessageBox::Cancel) == QMessageBox::Ok)
        {
            delete lstPatterns->takeItem(lstPatterns->currentRow());
        }
    }
}

