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

#include <QDialogButtonBox>
#include <QVBoxLayout>

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
