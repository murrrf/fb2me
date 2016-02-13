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

#include "recordeditor.h"
#include "person.h"

#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QGroupBox>
#include <QGridLayout>

RecordEditor::RecordEditor(FileRecord *rec, QWidget *parent) :
    QDialog(parent)
{
    boxButtons = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    connect(boxButtons, SIGNAL(accepted()), this, SLOT(accept()));
    connect(boxButtons, SIGNAL(rejected()), this, SLOT(reject()));

    boxMain = new QVBoxLayout();
    boxMain->addWidget(boxButtons);
    this->setLayout(boxMain);

    record = rec;
    updateUI();
}

RecordEditor::~RecordEditor()
{
    delete boxButtons;
    delete boxMain;
}

void RecordEditor::setData(FileRecord *rec)
{
    record = rec;
    updateUI();
}

void RecordEditor::updateUI()
{

}

//==============================================================================
// class AuthorDisplay
//==============================================================================

AuthorDisplay::AuthorDisplay(Person *author, int index, QWidget *parent)
{
    gbxAuthor = new QGroupBox();

    QGridLayout *tmpGrid = new QGridLayout();

    edtFirstName = new QLineEdit();
    edtFirstName->setReadOnly(true); // While there is no XML editing, data about the author only display
    edtFirstName->setText(author->getFirstName());
    tmpGrid->addWidget(edtFirstName, 0, 0);

    edtMiddleName = new QLineEdit();
    edtMiddleName->setReadOnly(true);
    edtMiddleName->setText(author->getMiddleName());
    tmpGrid->addWidget(edtMiddleName, 1, 0);

    edtLastName = new QLineEdit();
    edtLastName->setReadOnly(true);
    edtLastName->setText(author->getLastName());
    tmpGrid->addWidget(edtLastName, 2, 0);

    btnMoveDown = new QPushButton();
    btnMoveDown->setIcon(QIcon::fromTheme("go-down", QIcon(":/img/go-down.png")));
    connect(btnMoveDown, SIGNAL(clicked()), this, SIGNAL(MoveAuthorDown()));
    tmpGrid->addWidget(btnMoveDown, 0, 1);

    btnMoveUp = new QPushButton();
    btnMoveUp->setIcon(QIcon::fromTheme("go-up", QIcon(":/img/go-up.png")));
    connect(btnMoveUp, SIGNAL(clicked()), this, SIGNAL(MoveAuthorUp()));
    tmpGrid->addWidget(btnMoveUp, 1, 1);

    btnDeleteAuthor = new QPushButton();
    btnDeleteAuthor->setIcon(QIcon::fromTheme("edit-delete", QIcon(":/img/edit-delete.png")));
    connect(btnDeleteAuthor, SIGNAL(clicked()), this, SIGNAL(DeleteAuthor()));
    tmpGrid->addWidget(btnDeleteAuthor, 2, 1);

    gbxAuthor->setLayout(tmpGrid);
}

AuthorDisplay::~AuthorDisplay()
{
    delete btnDeleteAuthor;
    delete btnMoveUp;
    delete btnMoveDown;
    delete edtLastName;
    delete edtMiddleName;
    delete edtFirstName;
    delete gbxAuthor;
}
