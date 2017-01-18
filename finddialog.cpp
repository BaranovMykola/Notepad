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
    QString::iterator result;
    if(ui->down->isChecked())
    {
        QString::iterator beg = std::next(data.begin(), pointer.position());
        result = std::search(beg, data.end(), subject.begin(), subject.end());
    }
    else if(ui->up->isChecked())
    {
        std::string::const_reverse_iterator beg = std::prev(data.toStdString().rend(), pointer.position());
        std::string stdData = data.toStdString();
        auto result2 = std::search(stdData.crbegin(), stdData.crend(), subject.toStdString().crbegin(), subject.toStdString().crend());
        result = std::next(data.begin(), std::distance(stdData.crend(), result2));
    }

    if(result == data.end())
    {
        errorMessage(subject);
    }
    qDebug() << "Founded '" << subject << "' at " << std::distance(data.begin(), result) << "position. Moving cursor...";
    int firstPos = std::distance(data.begin(), result);
    int secondPos = firstPos+subject.length();
    selectText(firstPos, secondPos);
}

void FindDialog::errorMessage(QString subject)
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

void FindDialog::selectText(int from, int to)
{
    auto pointer = memo->textCursor();
    pointer.setPosition(from);
    pointer.setPosition(to, QTextCursor::KeepAnchor);
    memo->setTextCursor(pointer);
}
