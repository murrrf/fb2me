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
#include <QDialog>
#include <QLineEdit>
#include <QDialogButtonBox>
#include <QMessageBox>

SettingsHelper::SettingsHelper(const QString &title, QWidget *parent) :
    QGroupBox(parent)
{
    this->setTitle(title);

    tblData = new QTableWidget();
    tblData->setColumnCount(2); // Magic number. We don't need more (or less) columns
    setColumnHeaders(tr("Key"), tr("Value"));

    QPushButton *btnAdd = new QPushButton(tr("Add"));
    connect(btnAdd, SIGNAL(clicked()), this, SLOT(onAdd()));
    QPushButton *btnEdit = new QPushButton(tr("Edit"));
    connect(btnEdit, SIGNAL(clicked()), this, SLOT(onEdit()));
    QPushButton *btnDelete = new QPushButton(tr("Delete"));
    connect(btnDelete, SIGNAL(clicked()), this, SLOT(onDelete()));
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

void SettingsHelper::setColumnHeaders(const QString &key, const QString &value)
{
    tblData->setHorizontalHeaderLabels(QStringList() << key << value);
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

setting_t SettingsHelper::getSettingsList()
{
    setting_t list;

    for (int i = 0; i < tblData->rowCount(); ++i)
    {
        list.append(qMakePair(tblData->item(i, 0)->text(), tblData->item(i, 1)->text()));
    }

    return list;
}

void SettingsHelper::setSettingsList(setting_t list)
{
    tblData->clear();
    tblData->setRowCount(0);
    setting_t::iterator it;

    for (it = list.begin(); it != list.end(); ++it)
    {
        addItem((*it).first, (*it).second);
    }
}

void SettingsHelper::onAdd()
{
    QDialog *input = new QDialog();
    QVBoxLayout *inputBox = new QVBoxLayout();
    QLabel *keyHelp = new QLabel(tr("Key"));
    QLineEdit *keyText = new QLineEdit();
    QLabel *valueHelp = new QLabel(tr("Value"));
    QLineEdit *valueText = new QLineEdit();
    QDialogButtonBox *btnBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

    inputBox->addWidget(keyHelp);
    inputBox->addWidget(keyText);
    inputBox->addWidget(valueHelp);
    inputBox->addWidget(valueText);
    inputBox->addWidget(btnBox);
    input->setLayout(inputBox);

    connect(btnBox, SIGNAL(accepted()), input, SLOT(accept()));
    connect(btnBox, SIGNAL(rejected()), input, SLOT(reject()));

    if (input->exec() == QDialog::Accepted)
    {
        if ((!keyText->text().trimmed().isEmpty()) && (!valueText->text().trimmed().isEmpty()))
            addItem(keyText->text().trimmed(), valueText->text().trimmed());
    }

    delete input;
}

void SettingsHelper::onEdit()
{
    if (currentRow() > -1)
    {
        QDialog *input = new QDialog();
        QVBoxLayout *inputBox = new QVBoxLayout();
        QLabel *keyHelp = new QLabel(tr("Key"));
        QLineEdit *keyText = new QLineEdit(tblData->item(currentRow(), 0)->text());
        QLabel *valueHelp = new QLabel(tr("Value"));
        QLineEdit *valueText = new QLineEdit(tblData->item(currentRow(), 1)->text());
        QDialogButtonBox *btnBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

        inputBox->addWidget(keyHelp);
        inputBox->addWidget(keyText);
        inputBox->addWidget(valueHelp);
        inputBox->addWidget(valueText);
        inputBox->addWidget(btnBox);
        input->setLayout(inputBox);

        connect(btnBox, SIGNAL(accepted()), input, SLOT(accept()));
        connect(btnBox, SIGNAL(rejected()), input, SLOT(reject()));

        if (input->exec() == QDialog::Accepted)
        {
            if ((!keyText->text().trimmed().isEmpty()) && (!valueText->text().trimmed().isEmpty()))
                editItem(currentRow(), keyText->text().trimmed(), valueText->text().trimmed());
        }

        delete input;
        tblData->setCurrentCell(-1, -1);
    }
}

void SettingsHelper::onDelete()
{
    if (currentRow() > -1)
    {
        tblData->removeRow(currentRow());
        tblData->setCurrentCell(-1, -1);
    }
}
