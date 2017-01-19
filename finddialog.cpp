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
    auto pointer = memo->textCursor();
    if(ui->whatFind->text().isEmpty())
    {
        errorMessage("", "Cannot found empty word");
        pointer.clearSelection();
    }
    else
    {
        qDebug() << "position: " << pointer.position();
        QString data = memo->toPlainText();
        QString subject = ui->whatFind->text();
        if(!ui->matchCase->isChecked())
        {
            data = data.toLower();
            subject = subject.toLower();
        }
        QString::iterator result;
        int firstPos;
        int secondPos;
        QString::iterator beg = std::next(data.begin(), pointer.position());
        if(ui->down->isChecked())
        {
            result = std::search(beg, data.end(), subject.begin(), subject.end());
            firstPos = std::distance(data.begin(), result);
            secondPos = firstPos+subject.length();
        }
        else if(ui->up->isChecked())
        {
            pointer.setPosition(pointer.selectionStart()); //take fisrt pos of selection.
            pointer.clearSelection();

            std::string stdData = data.toStdString();
            auto stdSubject = subject.toStdString();
            std::string::reverse_iterator rbeg = std::next(stdData.rbegin(), abs(pointer.position()-stdData.length()));
            //take reverse_iterator of current pos
//            auto reverseResult = std::search(rbeg, stdData.rend(), stdSubject.rbegin(), stdSubject.rend());
            auto reverseResult = std::search(std::next(data.rbegin(), abs(pointer.position()-data.length())),
                                             data.rend(), subject.rbegin(), subject.rend());
//            result = std::next(data.begin(), std::distance(stdData.begin(), reverseResult.base()));
            result = reverseResult.base();
            firstPos = std::distance(data.begin(), result)-subject.length();
            secondPos = firstPos+subject.length();
        }

        if( ( result == data.end() && ui->down->isChecked() ) || ( result == data.begin() && ui->up->isChecked() ) )
        {
            errorMessage(subject);
        }
        else
        {
            qDebug() << "Founded '" << subject << "' at " << std::distance(data.begin(), result) << "position. Moving cursor...";
            selectText(firstPos, secondPos, pointer);
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
