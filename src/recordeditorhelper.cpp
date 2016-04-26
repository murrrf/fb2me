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
#include <QToolButton>
#include <QGroupBox>
#include <QVariant>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QSpinBox>
#include <QDialog>

RecordEditorHelper::RecordEditorHelper(int index, QWidget *parent) :
    QGroupBox(parent)
{
    boxLeft = new QVBoxLayout();

    boxRight = new QVBoxLayout();

    btnMoveUp = new QToolButton();
    btnMoveUp->setIcon(QIcon::fromTheme("go-up", QIcon(":/img/go-up.png")));
    btnMoveUp->setProperty("index", index);
    connect(btnMoveUp, SIGNAL(clicked()), this, SIGNAL(MoveUp()));
    boxRight->addWidget(btnMoveUp);

    btnMoveDown = new QToolButton();
    btnMoveDown->setIcon(QIcon::fromTheme("go-down", QIcon(":/img/go-down.png")));
    btnMoveDown->setProperty("index", index);
    connect(btnMoveDown, SIGNAL(clicked()), this, SIGNAL(MoveDown()));
    boxRight->addWidget(btnMoveDown);

    btnDelete = new QToolButton();
    btnDelete->setIcon(QIcon::fromTheme("edit-delete", QIcon(":/img/edit-delete.png")));
    btnDelete->setProperty("index", index);
    connect(btnDelete, SIGNAL(clicked()), this, SIGNAL(Delete()));
    boxRight->addWidget(btnDelete);

    boxMain = new QHBoxLayout();
    boxMain->addLayout(boxLeft);
    boxMain->addLayout(boxRight);

    this->setLayout(boxMain);
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
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

    QHBoxLayout *box = new QHBoxLayout();
    box->addWidget(lbl);
    box->addWidget(wgt);

    boxLeft->addLayout(box);

    return wgt;
}

void RecordEditorHelper::clearItems()
{
    for (int i = 0; i < itemList.count(); ++i)
    {
        QWidget *wgt = itemList.at(i);

        if (qobject_cast<QLineEdit *>(wgt) != 0)
        {
            qobject_cast<QLineEdit *>(wgt)->clear();
        }

        if (qobject_cast<QSpinBox *>(wgt) != 0)
        {
            qobject_cast<QSpinBox *>(wgt)->clear();
        }

        if (qobject_cast<QComboBox *>(wgt) != 0)
        {
            qobject_cast<QComboBox *>(wgt)->setCurrentIndex(-1);
        }
    }
}

//==============================================================================
// class RecordEditorHelperContainer
//==============================================================================

RecordEditorHelperContainer::RecordEditorHelperContainer(const QString &title, QWidget *parent):
    QGroupBox(parent), cntItems(0)
{
    this->setTitle(title);

    boxMain = new QVBoxLayout();

    btnAdd = new QToolButton();
    btnAdd->setIcon(QIcon::fromTheme("list-add", QIcon(":/img/list-add.png")));
    connect(btnAdd, SIGNAL(clicked()), this, SIGNAL(Add()));

    QHBoxLayout *tmpBtnBox = new QHBoxLayout();
    tmpBtnBox->addStretch();
    tmpBtnBox->addWidget(btnAdd);

    boxMain->addLayout(tmpBtnBox);

    this->setLayout(boxMain);
}

RecordEditorHelperContainer::~RecordEditorHelperContainer()
{
    delete btnAdd;
    delete boxMain;
}

void RecordEditorHelperContainer::addItem(RecordEditorHelper *item)
{
    boxMain->insertWidget(boxMain->count() - 1, item);
    connect(item, SIGNAL(Delete()), this, SLOT(onDeleteItem()));
    cntItems++;
}

void RecordEditorHelperContainer::insertWidget(int index, QWidget *widget)
{
    boxMain->insertWidget(index, widget);
}

void RecordEditorHelperContainer::insertLayout(int index, QLayout *layout)
{
    boxMain->insertLayout(index, layout);
}

void RecordEditorHelperContainer::onDeleteItem()
{
    if (cntItems > 1)
    {
        delete sender();
        cntItems--;
        adjustSize();
    }
    else
    {
        qobject_cast<RecordEditorHelper *>(sender())->clearItems();
    }

    if (qobject_cast<QDialog *>(parent()) != 0)
        (qobject_cast<QDialog *>(parent()))->adjustSize();
}
