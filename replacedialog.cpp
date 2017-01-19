#include "replacedialog.h"
#include "ui_replacedialog.h"

ReplaceDialog::ReplaceDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ReplaceDialog)
{
    ui->setupUi(this);
    connect(ui->buttonCancel, SIGNAL(clicked(bool)), this, SLOT(slotCancel()), Qt::UniqueConnection);
    connect(ui->buttonFindNext, SIGNAL(clicked(bool)), this, SLOT(slotFindNext()), Qt::UniqueConnection);

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

void ReplaceDialog::slotFindNext()
{
    mFindMenu->slotFindNext(true, ui->findWhat->text());
}

void ReplaceDialog::setFindDialog(FindDialog* findMenu)
{
    mFindMenu = findMenu;
}
