#include "loadingfontsdialog.h"
#include "ui_loadingfontsdialog.h"

LoadingFontsDialog::LoadingFontsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoadingFontsDialog)
{
    ui->setupUi(this);
    this->setWindowFlags(this->windowFlags() | Qt::MSWindowsFixedSizeDialogHint | Qt::WindowStaysOnTopHint);
}

LoadingFontsDialog::~LoadingFontsDialog()
{
    delete ui;
}
