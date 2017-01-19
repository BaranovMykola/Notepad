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
#include "mainwindow.h"

FindDialog::FindDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FindDialog)
{
    ui->setupUi(this);
    this->setWindowFlags(this->windowFlags() | Qt::MSWindowsFixedSizeDialogHint);
    this->setWindowFlags(this->windowFlags() ^ (Qt::CustomizeWindowHint | Qt::WindowStaysOnTopHint));

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
        if( ( result == data.end() && ui->down->isChecked() ) || ( result == data.begin() && ui->up->isChecked() ) )
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
