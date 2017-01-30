#include "duplexprintdialog.h"
#include "ui_duplexprintdialog.h"

DuplexPrintDialog::DuplexPrintDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DuplexPrintDialog)
{
    ui->setupUi(this);
    this->setWindowFlags(this->windowFlags() | Qt::MSWindowsFixedSizeDialogHint);
    this->setWindowModality(Qt::ApplicationModal);
}

DuplexPrintDialog::~DuplexPrintDialog()
{
    delete ui;
}
