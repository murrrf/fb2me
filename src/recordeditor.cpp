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
#include <QStackedLayout>

RecordEditor::RecordEditor(FileRecord *rec, QWidget *parent) :
    QDialog(parent)
{
    boxButtons = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    connect(boxButtons, SIGNAL(accepted()), this, SLOT(accept()));
    connect(boxButtons, SIGNAL(rejected()), this, SLOT(reject()));

    boxMain = new QVBoxLayout();
    this->setLayout(boxMain);
    this->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);

    lblBookTitle = new QLabel(tr("Book title"));

    edtBookTitle = new QLineEdit();
    edtBookTitle->setReadOnly(true);

    gbxAuthorList = new AuthorContainer(tr("List of authors"), this);

    gbxSeriesList = new SeriesContainer(tr("List of series"), this);

    gbxGenresList = new GenresContainer(tr("List of genres"), this);

    record = rec;
    updateUI();
}

RecordEditor::~RecordEditor()
{
    delete edtBookTitle;
    delete lblBookTitle;
    delete gbxGenresList;
    delete gbxSeriesList;
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

    for (int i = 0; i < record->getAuthorCount(); i++)
    {
        Person tmpAuthor = record->getAuthor(i);
        AuthorDisplay *tmp = new AuthorDisplay(&tmpAuthor, i, gbxAuthorList);
        gbxAuthorList->addItem(tmp, tmpAuthor.getFullNameLFM());
    }

    sequence_t tmpSequence = record->getSequenceList();

    for (int i = 0; i < tmpSequence.size(); i++)
    {
        SeriesDisplay *tmp = new SeriesDisplay(&tmpSequence, i, gbxSeriesList);
        gbxSeriesList->addItem(tmp);
    }

    genre_t tmpGenres = record->getGenresList();

    for (int i = 0; i < tmpGenres.size(); i++)
    {
        GenresDisplay *tmp = new GenresDisplay(&tmpGenres, i, gbxGenresList);
        gbxGenresList->addItem(tmp);
    }

    // Add new UI components to layout

    boxMain->addWidget(lblBookTitle);
    boxMain->addWidget(edtBookTitle);
    boxMain->addWidget(gbxAuthorList);
    boxMain->addWidget(gbxSeriesList);
    boxMain->addWidget(gbxGenresList);
    boxMain->addStretch();
    boxMain->addWidget(boxButtons);
}

//==============================================================================
// class AuthorDisplay
//==============================================================================

AuthorDisplay::AuthorDisplay(Person *author, int index, QWidget *parent):
    RecordEditorHelper(index, parent)
{
    QLineEdit *edtFirstName = qobject_cast<QLineEdit *>(addItem(ftLineEdit, tr("First name")));
    edtFirstName->setReadOnly(true); // While there is no XML editing, data about the author only display
    edtFirstName->setText(author->getFirstName());

    QLineEdit *edtMiddleName = qobject_cast<QLineEdit *>(addItem(ftLineEdit, tr("Middle name")));
    edtMiddleName->setReadOnly(true);
    edtMiddleName->setText(author->getMiddleName());

    QLineEdit *edtLastName = qobject_cast<QLineEdit *>(addItem(ftLineEdit, tr("Last name")));
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
    QLineEdit *edtName = qobject_cast<QLineEdit *>(addItem(ftLineEdit, tr("Name of sequence")));
    edtName->setReadOnly(true);
    edtName->setText(series->at(index).first);

    QLineEdit *edtNumber = qobject_cast<QLineEdit *>(addItem(ftLineEdit, tr("Number of book in sequence")));
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
    QComboBox *cbGenre = qobject_cast<QComboBox *>(addItem(ftComboBox, tr("Genre")));
    cbGenre->addItem(genres->at(index).first); // In the future there will be filling out a list of genres
    cbGenre->setCurrentIndex(cbGenre->findText(genres->at(index).first));

    QLineEdit *edtGenreMatch = qobject_cast<QLineEdit *>(addItem(ftLineEdit, tr("Genre match")));
    edtGenreMatch->setText(QString::number(genres->at(index).second));
}

GenresDisplay::~GenresDisplay()
{

}

//==============================================================================
// class AuthorContainer
//==============================================================================

AuthorContainer::AuthorContainer(const QString &title, QWidget *parent):
    RecordEditorHelperContainer(title, parent)
{
    cbAuthorSelect = new QComboBox(this);
    insertWidget(0, cbAuthorSelect);
    boxStacked = new QStackedLayout();
    insertLayout(1, boxStacked);
    connect(cbAuthorSelect, SIGNAL(currentIndexChanged(int)), boxStacked, SLOT(setCurrentIndex(int)));
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
}

AuthorContainer::~AuthorContainer()
{
    delete boxStacked;
    delete cbAuthorSelect;
}

void AuthorContainer::addItem(RecordEditorHelper *item, const QString &title)
{
    boxStacked->addWidget(item);
    cbAuthorSelect->addItem(title);
}

void AuthorContainer::onAddAuthor()
{
    // TODO It is necessary to come up with an algorithm to add a new author based on the fact that the authors are displayed at a time, not simultaneously.
}

//==============================================================================
// class SeriesContainer
//==============================================================================

SeriesContainer::SeriesContainer(const QString &title, QWidget *parent):
    RecordEditorHelperContainer(title, parent)
{
    connect(this, SIGNAL(Add()), this, SLOT(onAddSeries()));
}

SeriesContainer::~SeriesContainer()
{

}

void SeriesContainer::onAddSeries()
{
    sequence_t tmp;
    tmp.append(qMakePair(QString(""), 0));
    SeriesDisplay *newSeries = new SeriesDisplay(&tmp, 0, this);
    addItem(newSeries);
}

//==============================================================================
// class GenresContainer
//==============================================================================

GenresContainer::GenresContainer(const QString &title, QWidget *parent):
    RecordEditorHelperContainer(title, parent)
{
    connect(this, SIGNAL(Add()), this, SLOT(onAddGenre()));
}

GenresContainer::~GenresContainer()
{

}

void GenresContainer::onAddGenre()
{
    genre_t tmp;
    tmp.append(qMakePair(QString(""), 100));
    GenresDisplay *newGenre = new GenresDisplay(&tmp, 0, this);
    addItem(newGenre);
}
