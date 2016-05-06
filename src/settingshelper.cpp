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

#include "settingshelper.h"

#include <QTableWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>

SettingsHelper::SettingsHelper(const QString &title, QWidget *parent) :
    QGroupBox(parent)
{
    this->setTitle(title);

    tblData = new QTableWidget();
    tblData->setColumnCount(2); // Magic number. We don't need more (or less) columns
    tblData->setHorizontalHeaderLabels(QStringList() << tr("Key") << tr("Value"));

    QPushButton *btnAdd = new QPushButton(tr("Add"));
    connect(btnAdd, SIGNAL(clicked()), this, SIGNAL(Add()));
    QPushButton *btnEdit = new QPushButton(tr("Edit"));
    connect(btnEdit, SIGNAL(clicked()), this, SIGNAL(Edit()));
    QPushButton *btnDelete = new QPushButton(tr("Delete"));
    connect(btnDelete, SIGNAL(clicked()), this, SIGNAL(Delete()));
    QHBoxLayout *boxButtons = new QHBoxLayout();
    boxButtons->addWidget(btnAdd);
    boxButtons->addWidget(btnEdit);
    boxButtons->addWidget(btnDelete);

    boxMain = new QVBoxLayout();
    boxMain->addWidget(tblData);
    boxMain->addLayout(boxButtons);
    this->setLayout(boxMain);
}

SettingsHelper::~SettingsHelper()
{
    delete tblData;
    delete boxMain;
}

void SettingsHelper::setHelpString(const QString &help)
{
    if (qobject_cast<QLabel *>(boxMain->itemAt(0)->widget()) == 0)
    {
        boxMain->insertWidget(0, new QLabel());
    }

    qobject_cast<QLabel *>(boxMain->itemAt(0)->widget())->setText(help);

//    if (qobject_cast<QLabel *>(boxMain->itemAt(0)->widget()) != 0)
//    {
//        qobject_cast<QLabel *>(boxMain->itemAt(0)->widget())->setText(help);
//    }
//    else
//    {
//        QLabel *lblHelp = new QLabel();
//        lblHelp->setText(help);
//        boxMain->insertWidget(0, lblHelp);
//    }
}

int SettingsHelper::currentRow()
{
    return tblData->currentRow();
}

void SettingsHelper::addItem(const QString &key, const QString &value)
{
    tblData->setRowCount(tblData->rowCount() + 1);
    QTableWidgetItem *keyItem = new QTableWidgetItem(key);
    QTableWidgetItem *valueItem = new QTableWidgetItem(value);
    tblData->setItem(tblData->rowCount() - 1, 0, keyItem);
    tblData->setItem(tblData->rowCount() - 1, 1, valueItem);
}

void SettingsHelper::editItem(const int row, const QString &key, const QString &value)
{
    tblData->item(row, 0)->setText(key);
    tblData->item(row, 1)->setText(value);
}
