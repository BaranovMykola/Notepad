#include "loadingdialog.h"
#include "ui_loadngdialog.h"

#include "fontdialog.h"

LoadingDialog::LoadingDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoadingDialog)
{
    ui->setupUi(this);
    this->setWindowTitle("Loading...");
    ui->progressBar->setWhatsThis("Loading systems fonts...");
    this->setWindowFlags(this->windowFlags() | Qt::MSWindowsFixedSizeDialogHint | Qt::WindowStaysOnTopHint);
}

LoadingDialog::~LoadingDialog()
{
    delete ui;
}
