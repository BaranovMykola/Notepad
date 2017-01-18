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

//void FindDialog::setMain(MainWindow *_main)
//{
//    mainWindow = _main;
//}

void FindDialog::slotCancel()
{
    this->hide();
}

void FindDialog::slotFindNext()
{
    auto pointer = memo->textCursor();
    qDebug() << "position: " << pointer.position();
    QString data = memo->toPlainText();
    QString subject = ui->whatFind->text();
    QString::iterator result;
    int firstPos;
    int secondPos;
    QString::iterator beg = std::next(data.begin(), pointer.position());
    if(ui->down->isChecked())
    {
        result = std::search(beg, data.end(), subject.begin(), subject.end());
        secondPos = firstPos+subject.length();
        firstPos = std::distance(data.begin(), result);
    }
    else if(ui->up->isChecked())
    {
        pointer.setPosition(pointer.selectionStart());
        pointer.clearSelection();
        qDebug() << "selection: " << pointer.selectionStart() << " - " << pointer.selectionEnd();
        qDebug() << "Started pos: " << pointer.position();
        std::string::const_reverse_iterator beg = std::prev(data.toStdString().rend(), pointer.position());
        std::string stdData = data.toStdString();
        std::cout << std::endl;
        auto stdSubject = subject.toStdString();
//        for(auto i = stdSubject.crbegin();i!= stdSubject.crend();++i)
//        {
//            std::cout << *i;
//        }
        std::cout << std::endl << std::endl;
        std::string::reverse_iterator rbeg = std::next(stdData.rbegin(), abs(pointer.position()-stdData.length()));
//        for(auto i = rbeg;i!= stdData.crend();++i)
//        {
//            qDebug() << *i;
//        }
        auto result2 = std::search(rbeg, stdData.rend(), stdSubject.rbegin(), stdSubject.rend());
        result = std::next(data.begin(), std::distance(stdData.begin(), result2.base()));
        firstPos = std::distance(data.begin(), result)-subject.length();
        secondPos = firstPos+subject.length();
        qDebug() << "First pos of founded value: " << firstPos << " Second pos: " << secondPos;
//        pointer.setPosition(firstPos);
    }

    if(result == data.end() && ui->down->isChecked() || result == data.begin() && ui->up->isChecked())
    {
        errorMessage(subject);
    }
    qDebug() << "Founded '" << subject << "' at " << std::distance(data.begin(), result) << "position. Moving cursor...";
    selectText(firstPos, secondPos, pointer);
//    pointer = memo->textCursor();
//    pointer.clearSelection();
//    memo->setTextCursor(pointer);
}

void FindDialog::errorMessage(QString subject)
{
    QMessageBox errorMessage;
    QString message = NotFoundMessage;
    message.arg(subject);
    errorMessage.setText(message);
    errorMessage.setIcon(QMessageBox::Information);
    errorMessage.setWindowTitle("Notepad");
    this->hide();
    errorMessage.exec();
}

void FindDialog::selectText(int from, int to, QTextCursor &pointer)
{
//    auto pointer = memo->textCursor();
    pointer.setPosition(from);
    pointer.setPosition(to, QTextCursor::KeepAnchor);
    memo->setTextCursor(pointer);
}
