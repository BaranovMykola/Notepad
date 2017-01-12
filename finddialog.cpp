#include "finddialog.h"
#include "ui_finddialog.h"

#include "mainwindow.h"

#include <QPlainTextEdit>
#include <QDebug>
#include <iterator>
#include <algorithm>
#include <QTextCursor>
#include <QMessageBox>

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
    auto beg = std::next(data.begin(), pointer.position());
    auto result = std::search(beg, data.end(), subject.begin(), subject.end());
    if(result == data.end())
    {
        QMessageBox errorMessage;
        QString message = NotFoundMessage;
        message.append("'");
        message.append(subject);
        message.append("'");
        errorMessage.setText(message);
        errorMessage.setIcon(QMessageBox::Information);
        errorMessage.setWindowTitle("Notepad");
        this->hide();
        errorMessage.exec();
    }
    qDebug() << "Founded '" << subject << "' at " << std::distance(data.begin(), result) << "position. Moving cursor...";
    int firstPos = std::distance(data.begin(), result);
    int secondPos = firstPos+subject.length();
    pointer.setPosition(firstPos);
    pointer.setPosition(secondPos, QTextCursor::KeepAnchor);
    memo->setTextCursor(pointer);
}

