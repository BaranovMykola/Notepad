#include "loadingdialog.h"
#include "ui_loadngdialog.h"

#include "fontdialog.h"

LoadingDialog::LoadingDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoadingDialog)
{
    ui->setupUi(this);
}

LoadingDialog::~LoadingDialog()
{
    delete ui;
}
