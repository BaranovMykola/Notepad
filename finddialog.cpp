#include "finddialog.h"
#include "ui_finddialog.h"

#include "mainwindow.h"

#include <QPlainTextEdit>
#include <QDebug>
#include <iterator>
#include <algorithm>

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

void FindDialog::setMemo(QPlainTextEdit *memo)
{
    mMemo = memo;
//    mCurrent = memo->textCursor();
}

void FindDialog::slotCancel()
{
    this->hide();
}

//void FindDialog::slotFindNext()
//{
//    qDebug() << "position: " << mCurrent.position();
//    QString data = mMemo->toPlainText();
//    auto beg = std::next(data.begin(), mCurrent.position());
//}

//void FindDialog::updateCursor()
//{
//    mCurrent = mMemo->textCursor();
//}
