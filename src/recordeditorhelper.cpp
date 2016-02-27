/***********************************************************************
 *
 * Copyright (C) 2016 Sergej Martynov <veter@veter.name>
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

#include "recordeditorhelper.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QGroupBox>
#include <QVariant>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QSpinBox>

RecordEditorHelper::RecordEditorHelper(int index, QWidget *parent) :
    QGroupBox(parent)
{
    boxLeft = new QVBoxLayout();

    boxRight = new QVBoxLayout();

    btnMoveUp = new QPushButton();
    btnMoveUp->setIcon(QIcon::fromTheme("go-up", QIcon(":/img/go-up.png")));
    btnMoveUp->setProperty("index", index);
    connect(btnMoveUp, SIGNAL(clicked()), this, SIGNAL(MoveUp()));
    boxRight->addWidget(btnMoveUp);

    btnMoveDown = new QPushButton();
    btnMoveDown->setIcon(QIcon::fromTheme("go-down", QIcon(":/img/go-down.png")));
    btnMoveDown->setProperty("index", index);
    connect(btnMoveDown, SIGNAL(clicked()), this, SIGNAL(MoveDown()));
    boxRight->addWidget(btnMoveDown);

    btnDelete = new QPushButton();
    btnDelete->setIcon(QIcon::fromTheme("edit-delete", QIcon(":/img/edit-delete.png")));
    btnDelete->setProperty("index", index);
    connect(btnDelete, SIGNAL(clicked()), this, SIGNAL(Delete()));
    boxRight->addWidget(btnDelete);

    boxRight->addStretch();

    boxMain = new QHBoxLayout();
    boxMain->addLayout(boxLeft);
    boxMain->addLayout(boxRight);

    this->setLayout(boxMain);
}

RecordEditorHelper::~RecordEditorHelper()
{
    delete btnDelete;
    delete btnMoveDown;
    delete btnMoveUp;
    delete boxRight;
    delete boxLeft;
    delete boxMain;
}

QWidget *RecordEditorHelper::addItem(FieldType ft, QString label)
{
    QWidget *wgt;

    switch (ft)
    {
    case ftLineEdit:
        wgt = new QLineEdit(this);
        break;

    case ftSpinEdit:
        wgt = new QSpinBox(this);
        break;

    case ftComboBox:
        wgt = new QComboBox(this);

    default:
        break;
    }

    itemList.append(wgt);

    QLabel *lbl = new QLabel(label, this);

    boxLeft->addWidget(lbl);
    boxLeft->addWidget(wgt);

    return wgt;
}
