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
#include "filerecord.h"
#include "person.h"

#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QGroupBox>
#include <QGridLayout>
#include <QComboBox>

RecordEditor::RecordEditor(FileRecord *rec, QWidget *parent) :
    QDialog(parent)
{
    boxButtons = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    connect(boxButtons, SIGNAL(accepted()), this, SLOT(accept()));
    connect(boxButtons, SIGNAL(rejected()), this, SLOT(reject()));

    boxMain = new QVBoxLayout();
    this->setLayout(boxMain);

    lblBookTitle = new QLabel(trUtf8("Book title"));

    edtBookTitle = new QLineEdit();
    edtBookTitle->setReadOnly(true);

    gbxAuthorList = new QGroupBox(trUtf8("List of authors"));
    boxAuthorList = new QVBoxLayout();

    gbxSeriesList = new QGroupBox(trUtf8("List of series"));
    boxSeriesList = new QVBoxLayout();

    gbxGenresList = new QGroupBox(trUtf8("List of genres"));
    boxSeriesList = new QVBoxLayout();

    record = rec;
    updateUI();
}

RecordEditor::~RecordEditor()
{
    delete edtBookTitle;
    delete lblBookTitle;
    delete boxGenresList;
    delete gbxGenresList;
    delete boxSeriesList;
    delete gbxSeriesList;
    delete boxAuthorList;
    delete gbxAuthorList;
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
    // Remove old UI

//    QVector<AuthorDisplay *>::iterator it = authorList.end();
//
//    while (it != authorList.begin())
//    {
//        --it;
//        delete(*it);
//    }
//
//    authorList.clear();
//
//    while ((boxMain->takeAt(0)) != 0)
//    {
//    }

    // Make updated UI

    edtBookTitle->setText(record->getBookTitle());

    gbxAuthorList->setLayout(boxAuthorList);

    for (int i = 0; i < record->getAuthorCount(); i++)
    {
        Person tmpAuthor = record->getAuthor(i);
        AuthorDisplay *tmp = new AuthorDisplay(&tmpAuthor, i, gbxAuthorList);
        boxAuthorList->addWidget(tmp);
//        authorList.append(tmp);
    }


    gbxSeriesList->setLayout(boxSeriesList);

    for (int i = 0; i < record->getSequenceList().size(); i++)
    {
        sequence_t tmpSequence = record->getSequenceList();
        SeriesDisplay *tmp = new SeriesDisplay(&tmpSequence, i, gbxSeriesList);
        boxSeriesList->addWidget(tmp);
    }

    gbxGenresList->setLayout(boxGenresList);
    genre_t tmpGenres = record->getSequenceList();

    for (int i = 0; i < tmpGenres.size(); i++)
    {
        GenresDisplay *tmp = new GenresDisplay(&tmpGenres, i, gbxGenresList);
        boxGenresList->addWidget(tmp);
    }

    // Add new UI components to layout

    boxMain->addWidget(lblBookTitle);
    boxMain->addWidget(edtBookTitle);
    boxMain->addWidget(gbxAuthorList);
    boxMain->addWidget(gbxSeriesList);
    boxMain->addWidget(boxButtons);
}

//==============================================================================
// class AuthorDisplay
//==============================================================================

AuthorDisplay::AuthorDisplay(Person *author, int index, QWidget *parent):
    QWidget(parent)
{
    this->setMinimumSize(100, 100);

    gbxAuthor = new QGroupBox();

    QVBoxLayout *boxLeft = new QVBoxLayout();

    lblFirstName = new QLabel(trUtf8("First name"));
    boxLeft->addWidget(lblFirstName);

    edtFirstName = new QLineEdit();
    edtFirstName->setReadOnly(true); // While there is no XML editing, data about the author only display
    edtFirstName->setText(author->getFirstName());
    boxLeft->addWidget(edtFirstName);

    lblMiddleName = new QLabel(trUtf8("Middle name"));
    boxLeft->addWidget(lblMiddleName);

    edtMiddleName = new QLineEdit();
    edtMiddleName->setReadOnly(true);
    edtMiddleName->setText(author->getMiddleName());
    boxLeft->addWidget(edtMiddleName);

    lblLastName = new QLabel(trUtf8("Last name"));
    boxLeft->addWidget(lblLastName);

    edtLastName = new QLineEdit();
    edtLastName->setReadOnly(true);
    edtLastName->setText(author->getLastName());
    boxLeft->addWidget(edtLastName);

    boxLeft->addStretch();

    QVBoxLayout *boxRight = new QVBoxLayout();

    boxRight->addWidget(new QLabel());

    btnMoveUp = new QPushButton();
    btnMoveUp->setIcon(QIcon::fromTheme("go-up", QIcon(":/img/go-up.png")));
    btnMoveUp->setProperty("index", index);
    connect(btnMoveUp, SIGNAL(clicked()), this, SIGNAL(MoveAuthorUp()));
    boxRight->addWidget(btnMoveUp);

    btnMoveDown = new QPushButton();
    btnMoveDown->setIcon(QIcon::fromTheme("go-down", QIcon(":/img/go-down.png")));
    btnMoveDown->setProperty("index", index);
    connect(btnMoveDown, SIGNAL(clicked()), this, SIGNAL(MoveAuthorDown()));
    boxRight->addWidget(btnMoveDown);

    btnDeleteAuthor = new QPushButton();
    btnDeleteAuthor->setIcon(QIcon::fromTheme("edit-delete", QIcon(":/img/edit-delete.png")));
    btnDeleteAuthor->setProperty("index", index);
    connect(btnDeleteAuthor, SIGNAL(clicked()), this, SIGNAL(DeleteAuthor()));
    boxRight->addWidget(btnDeleteAuthor);

    boxRight->addStretch();

    QHBoxLayout *boxMain = new QHBoxLayout();
    boxMain->addLayout(boxLeft);
    boxMain->addLayout(boxRight);

    gbxAuthor->setLayout(boxMain);
    QVBoxLayout *tmp = new QVBoxLayout();
    tmp->addWidget(gbxAuthor);
    this->setLayout(tmp);
}

AuthorDisplay::~AuthorDisplay()
{
    delete btnDeleteAuthor;
    delete btnMoveUp;
    delete btnMoveDown;
    delete edtLastName;
    delete lblLastName;
    delete edtMiddleName;
    delete lblMiddleName;
    delete edtFirstName;
    delete lblFirstName;
    delete gbxAuthor;
}

//==============================================================================
// class SeriesDisplay
//==============================================================================

SeriesDisplay::SeriesDisplay(sequence_t *series, int index, QWidget *parent):
    QWidget(parent)
{
    this->setMinimumSize(100, 100);

    gbxSeries = new QGroupBox();

    QVBoxLayout *boxLeft = new QVBoxLayout();

    lblSeriesName = new QLabel(trUtf8("Name of sequence"));
    boxLeft->addWidget(lblSeriesName);

    edtSeriesName = new QLineEdit();
    edtSeriesName->setReadOnly(true); // While there is no XML editing, data about the author only display
    edtSeriesName->setText(series->at(index).first);
    boxLeft->addWidget(edtSeriesName);

    lblSeriesNumber = new QLabel(trUtf8("Number of book in sequence"));
    boxLeft->addWidget(lblSeriesNumber);

    edtSeriesNumber = new QLineEdit();
    edtSeriesNumber->setReadOnly(true);
    edtSeriesNumber->setText(QString::number(series->at(index).second));
    boxLeft->addWidget(edtSeriesNumber);

    boxLeft->addStretch();

    QVBoxLayout *boxRight = new QVBoxLayout();

    boxRight->addWidget(new QLabel());

    btnMoveUp = new QPushButton();
    btnMoveUp->setIcon(QIcon::fromTheme("go-up", QIcon(":/img/go-up.png")));
    btnMoveUp->setProperty("index", index);
    connect(btnMoveUp, SIGNAL(clicked()), this, SIGNAL(MoveAuthorUp()));
    boxRight->addWidget(btnMoveUp);

    btnMoveDown = new QPushButton();
    btnMoveDown->setIcon(QIcon::fromTheme("go-down", QIcon(":/img/go-down.png")));
    btnMoveDown->setProperty("index", index);
    connect(btnMoveDown, SIGNAL(clicked()), this, SIGNAL(MoveAuthorDown()));
    boxRight->addWidget(btnMoveDown);

    btnDeleteSeries = new QPushButton();
    btnDeleteSeries->setIcon(QIcon::fromTheme("edit-delete", QIcon(":/img/edit-delete.png")));
    btnDeleteSeries->setProperty("index", index);
    connect(btnDeleteSeries, SIGNAL(clicked()), this, SIGNAL(DeleteSeries()));
    boxRight->addWidget(btnDeleteSeries);

    boxRight->addStretch();

    QHBoxLayout *boxMain = new QHBoxLayout();
    boxMain->addLayout(boxLeft);
    boxMain->addLayout(boxRight);

    gbxSeries->setLayout(boxMain);
    QVBoxLayout *tmp = new QVBoxLayout();
    tmp->addWidget(gbxSeries);
    this->setLayout(tmp);
}

// TODO Make base class for all helpers

//==============================================================================
// class GenresDisplay
//==============================================================================

SeriesDisplay::~SeriesDisplay()
{
    delete btnDeleteSeries;
    delete btnMoveDown;
    delete btnMoveUp;
    delete edtSeriesNumber;
    delete lblSeriesNumber;
    delete edtSeriesName;
    delete lblSeriesName;
    delete gbxSeries;
}

GenresDisplay::GenresDisplay(genre_t *genres, int index, QWidget *parent):
    RecordEditorHelper(index, parent)
{
    QComboBox *cb = qobject_cast<QComboBox *>(addItem(ftComboBox, trUtf8("Genre")));
    cb->addItem(genres->at(index).first); // In the future there will be filling out a list of genres
    cb->setCurrentIndex(cb->findText(genres->at(index).first));
}
