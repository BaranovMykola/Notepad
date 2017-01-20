#include "loadingdialog.h"
#include "ui_loadngdialog.h"

#include "fontdialog.h"

LoadingDialog::LoadingDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoadingDialog)
{
    ui->setupUi(this);
}

void LoadingDialog::setRange(int from, int to)
{
    ui->progressBar->setRange(from, to);
}

void LoadingDialog::setValue(int value)
{
    ui->progressBar->setValue(value);
}

LoadingDialog::~LoadingDialog()
{
    delete ui;
}
