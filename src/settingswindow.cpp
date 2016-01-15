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

#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QLabel>
#include <QListWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QInputDialog>

SettingsWindow::SettingsWindow(QWidget *parent)
    : QDialog(parent)
{
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
}

SettingsWindow::~SettingsWindow()
{
    delete boxButtons;
    delete boxMain;
}

void SettingsWindow::onPatternAdd()
{
    bool ok;
    QString text = QInputDialog::getText(this, tr("Add new template"), tr("Enter template"), QLineEdit::Normal, "", &ok);

    if (ok && !text.isEmpty())
        lstPatterns->addItem(text);
}

void SettingsWindow::onPatternEdit()
{
    if (lstPatterns->currentRow() > -1)
    {
        bool ok;
        QString text = QInputDialog::getText(this, tr("Edit template"), tr("Enter template"), QLineEdit::Normal,
                                             lstPatterns->item(lstPatterns->currentRow())->text(), &ok);

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

}

