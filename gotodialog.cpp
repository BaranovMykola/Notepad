#include "gotodialog.h"
#include "ui_gotodialog.h"

#include "mainwindow.h"

GoToDialog::GoToDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GoToDialog)
{
    ui->setupUi(this);
}

GoToDialog::~GoToDialog()
{
    delete ui;
}
