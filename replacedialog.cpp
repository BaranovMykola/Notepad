//Copyright (C) 2017  Baranov Mykola

//This program is free software: you can redistribute it and/or modify
//it under the terms of the GNU General Public License as published by
//the Free Software Foundation, either version 3 of the License, or
//(at your option) any later version.

//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.

//You should have received a copy of the GNU General Public License
//along with this program.  If not, see http://www.gnu.org/licenses/

//// \brief Dialog finds and replaces text using FindDialog.


#include "replacedialog.h"
#include "ui_replacedialog.h"

#include <QPlainTextEdit>
#include <iostream>

ReplaceDialog::ReplaceDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ReplaceDialog)
{
    ui->setupUi(this);
    this->setWindowFlags(this->windowFlags() | Qt::MSWindowsFixedSizeDialogHint);
    connect(ui->buttonCancel, SIGNAL(clicked(bool)), this, SLOT(slotCancel()), Qt::UniqueConnection);
    connect(ui->buttonFindNext, SIGNAL(clicked(bool)), this, SLOT(slotFindNext()), Qt::UniqueConnection);
    connect(ui->buttonReplace, SIGNAL(clicked(bool)), this, SLOT(slotReplace()), Qt::UniqueConnection);
    connect(ui->buttonReplaceAll, SIGNAL(clicked(bool)), this, SLOT(slotReplaceAll()), Qt::UniqueConnection);
    connect(ui->findWhat, SIGNAL(textChanged(QString)), this, SLOT(slotEditRepalceWord()), Qt::UniqueConnection);

    ui->buttonFindNext->setShortcut(QKeySequence::FindNext);
}

ReplaceDialog::~ReplaceDialog()
{
    delete ui;
}

void ReplaceDialog::slotCancel()
{
    this->hide();
}

bool ReplaceDialog::slotFindNext()
{
    return mFindMenu->findNext(ui->findWhat->text(), FindDialog::Direction::Down, ui->matchCase->isChecked());
}

void ReplaceDialog::slotReplace()
{
    replace(true);
}

void ReplaceDialog::slotReplaceAll()
{
    int replaceCount = 0;
    while(replace(false))
    {
        ++replaceCount;
    }
    if(replaceCount)
    {
        mFindMenu->errorMessage(QString::number(replaceCount), ReplaceMessage);
    }
    else
    {
        mFindMenu->errorMessage(ui->findWhat->text(), NotFoundMessage);
    }
}

void ReplaceDialog::slotEditRepalceWord()
{
    bool enable = !ui->findWhat->text().isEmpty();
    ui->buttonFindNext->setEnabled(enable);
    ui->buttonReplace->setEnabled(enable);
    ui->buttonReplaceAll->setEnabled(enable);
}

bool ReplaceDialog::replace(bool errorReport)
{
    bool founded = slotFindNext();
    auto pointer = mFindMenu->memo->textCursor();
    if(founded)
    {
        pointer.removeSelectedText();
        pointer.insertText(ui->replaceWith->text());
    }
    else if(errorReport)
    {
        mFindMenu->errorMessage(ui->findWhat->text(), NotFoundMessage);
    }
    return founded;
}

void ReplaceDialog::setFindDialog(FindDialog* findMenu)
{
    mFindMenu = findMenu;
}
