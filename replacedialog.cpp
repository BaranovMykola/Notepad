#include "replacedialog.h"
#include "ui_replacedialog.h"

#include <QPlainTextEdit>
#include <iostream>

ReplaceDialog::ReplaceDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ReplaceDialog)
{
    ui->setupUi(this);
    connect(ui->buttonCancel, SIGNAL(clicked(bool)), this, SLOT(slotCancel()), Qt::UniqueConnection);
    connect(ui->buttonFindNext, SIGNAL(clicked(bool)), this, SLOT(slotFindNext()), Qt::UniqueConnection);
    connect(ui->buttonReplace, SIGNAL(clicked(bool)), this, SLOT(slotReplace()), Qt::UniqueConnection);
    connect(ui->buttonReplaceAll, SIGNAL(clicked(bool)), this, SLOT(slotReplaceAll()), Qt::UniqueConnection);

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
