#include "pageoptiondialog.h"
#include "ui_pageoptiondialog.h"

PageOptionDialog::PageOptionDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PageOptionDialog)
{
    ui->setupUi(this);
}

PageOptionDialog::~PageOptionDialog()
{
    delete ui;
}
