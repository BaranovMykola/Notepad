//************************************************************************
//    This module implement definition of FindDialog
//
//    Copyright (C) 2017 Baranov Mykola <mapsg32@gmail.com>
//
//    This program is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.

//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.

//    You should have received a copy of the GNU General Public License
//    along with this program.  If not, see <http://www.gnu.org/licenses/>
//************************************************************************

#include "finddialog.h"
#include "ui_finddialog.h"

#include "mainwindow.h"

#include <QPlainTextEdit>
#include <QDebug>
#include <iterator>
#include <algorithm>
#include <QTextCursor>
#include <QMessageBox>

#include <iostream>

FindDialog::FindDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FindDialog)
{
    ui->setupUi(this);
    this->setWindowFlags(this->windowFlags() | Qt::MSWindowsFixedSizeDialogHint);

    connect(ui->buttonCancel, SIGNAL(clicked(bool)), this, SLOT(slotCancel()), Qt::UniqueConnection);
    connect(ui->buttonFindNext, SIGNAL(clicked(bool)), this, SLOT(slotFindNext()), Qt::UniqueConnection);
}

FindDialog::~FindDialog()
{
    delete ui;
}

void FindDialog::setMemo(QPlainTextEdit *_memo)
{
    memo = _memo;
}

void FindDialog::slotCancel()
{
    this->hide();
}

void FindDialog::slotFindNext()
{
    Direction type;
    if(ui->down->isChecked())
    {
        type = Direction::Down;
    }
    else if(ui->up->isChecked())
    {
        type = Direction::Up;
    }
    else
    {
        errorMessage("", UndefinedDirectionMessage);
    }
    findNext(ui->whatFind->text(), type, ui->matchCase->isChecked(), true);
}

bool FindDialog::findNext(QString subject, Direction type, bool matchCase, bool errorReport)
{
    auto pointer = memo->textCursor();
    if(subject.isEmpty())
    {
        errorMessage("", "Cannot found empty word");
        pointer.clearSelection();
    }
    else
    {
        qDebug() << "position: " << pointer.position();
        QString data = memo->toPlainText();
//        QString subject = ui->whatFind->text();
        if(!matchCase)
        {
            data = data.toLower();
            subject = subject.toLower();
        }
        QString::iterator result;
        int firstPos;
        int secondPos;
        QString::iterator beg = std::next(data.begin(), pointer.position());
        if(type == Direction::Down)
        {
            result = std::search(beg, data.end(), subject.begin(), subject.end());
            firstPos = std::distance(data.begin(), result);
            secondPos = firstPos+subject.length();
        }
        else if(type == Direction::Up)
        {
            pointer.setPosition(pointer.selectionStart()); //take fisrt pos of selection.
            pointer.clearSelection();
            auto reverseResult = std::search(std::next(data.rbegin(), abs(pointer.position()-data.length())),
                                             data.rend(), subject.rbegin(), subject.rend());
            result = reverseResult.base();
            firstPos = std::distance(data.begin(), result)-subject.length();
            secondPos = firstPos+subject.length();
        }
        else
        {
            errorMessage("", UndefinedDirectionMessage);
        }
        if( ( result == data.end() && type == Direction::Down ) || ( result == data.begin() && type == Direction::Up ) )
        {
            if(errorReport)
            {
                pointer.clearSelection();
                errorMessage(subject);
            }
            return false;
            qDebug() << "Ended of file";
        }
        else
        {
            qDebug() << "Founded '" << subject << "' at " << std::distance(data.begin(), result) << "position. Moving cursor...";
            selectText(firstPos, secondPos, pointer);
            return true;
        }
    }
}

void FindDialog::errorMessage(QString subject, QString message)
{
    QMessageBox errorMessage;
    message = message.arg(subject);
    errorMessage.setText(message);
    errorMessage.setIcon(QMessageBox::Information);
    errorMessage.setWindowTitle("Notepad");
    this->hide();
    errorMessage.exec();
}

void FindDialog::selectText(int from, int to, QTextCursor &pointer)
{
    pointer.setPosition(from);
    pointer.setPosition(to, QTextCursor::KeepAnchor);
    memo->setTextCursor(pointer);
}
