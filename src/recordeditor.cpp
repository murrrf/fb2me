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
    boxGenresList = new QVBoxLayout();

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
    sequence_t tmpSequence = record->getSequenceList();

    for (int i = 0; i < tmpSequence.size(); i++)
    {
        SeriesDisplay *tmp = new SeriesDisplay(&tmpSequence, i, gbxSeriesList);
        boxSeriesList->addWidget(tmp);
    }

    gbxGenresList->setLayout(boxGenresList);
    genre_t tmpGenres = record->getGenresList();

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
    boxMain->addWidget(gbxGenresList);
    boxMain->addWidget(boxButtons);
}

//==============================================================================
// class AuthorDisplay
//==============================================================================

AuthorDisplay::AuthorDisplay(Person *author, int index, QWidget *parent):
    RecordEditorHelper(index, parent)
{
    QLineEdit *edtFirstName = qobject_cast<QLineEdit *>(addItem(ftLineEdit, trUtf8("First name")));
    edtFirstName->setReadOnly(true); // While there is no XML editing, data about the author only display
    edtFirstName->setText(author->getFirstName());

    QLineEdit *edtMiddleName = qobject_cast<QLineEdit *>(addItem(ftLineEdit, trUtf8("Middle name")));
    edtMiddleName->setReadOnly(true);
    edtMiddleName->setText(author->getMiddleName());

    QLineEdit *edtLastName = qobject_cast<QLineEdit *>(addItem(ftLineEdit, trUtf8("Middle name")));
    edtLastName->setReadOnly(true);
    edtLastName->setText(author->getLastName());
}

AuthorDisplay::~AuthorDisplay()
{

}

//==============================================================================
// class SeriesDisplay
//==============================================================================

SeriesDisplay::SeriesDisplay(sequence_t *series, int index, QWidget *parent):
    RecordEditorHelper(index, parent)
{
    QLineEdit *edtName = qobject_cast<QLineEdit *>(addItem(ftLineEdit, trUtf8("Name of sequence")));
    edtName->setReadOnly(true);
    edtName->setText(series->at(index).first);

    QLineEdit *edtNumber = qobject_cast<QLineEdit *>(addItem(ftLineEdit, trUtf8("Number of book in sequence")));
    edtNumber->setReadOnly(true);
    edtNumber->setText(QString::number(series->at(index).second));
}

SeriesDisplay::~SeriesDisplay()
{

}

//==============================================================================
// class GenresDisplay
//==============================================================================

GenresDisplay::GenresDisplay(genre_t *genres, int index, QWidget *parent):
    RecordEditorHelper(index, parent)
{
    QComboBox *cbGenre = qobject_cast<QComboBox *>(addItem(ftComboBox, trUtf8("Genre")));
    cbGenre->addItem(genres->at(index).first); // In the future there will be filling out a list of genres
    cbGenre->setCurrentIndex(cbGenre->findText(genres->at(index).first));
}

GenresDisplay::~GenresDisplay()
{

}
