//************************************************************************
//    This module implement definition of SaveDialog class
//
//    Copyright (C) 2017 Baranov Mykola <mapsg32@gmail.com>
//
//    This program is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.

//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.

//    You should have received a copy of the GNU General Public License
//    along with this program.  If not, see <http://www.gnu.org/licenses/>
//************************************************************************

#include "savedialog.h"
#include "ui_savedialog.h"

#include <QDebug>
#include <QFile>
#include <QFont>
#include <QPalette>
#include <QColor>
#include <QFileDialog>

#include "savefilefunction.h"
#include "constants.h"
#include "mainwindow.h"

SaveDialog::SaveDialog(QWidget *parent, MainWindow* _obj, QString data) :
    QDialog(parent),
    ui(new Ui::SaveDialog),
    obj(_obj),
    mData(data)
{
    ui->setupUi(this);
    this->setWindowFlags(this->windowFlags() | Qt::MSWindowsFixedSizeDialogHint);
    this->setWindowModality(Qt::ApplicationModal);
    QPalette sample_palette;
    sample_palette.setColor(QPalette::Window, Qt::white);
    sample_palette.setColor(QPalette::WindowText, QColor(0,60,150));
    auto filePath = obj->mFile.fileName();
    if(filePath.isEmpty())
    {
        filePath = "Untitled";
    }
    else
    {
        filePath.prepend("\n");
    }
    auto message = AskMessage;
    message.append(AskSeparator);
    message.append(filePath);
    ui->askMessage->setAutoFillBackground(true);
    ui->askMessage->setPalette(sample_palette);
    ui->askMessage->setText(message);
    connect(ui->buttonSave, SIGNAL(clicked(bool)), this, SLOT(slotSave()), Qt::UniqueConnection);
    connect(ui->buttonDontSave, SIGNAL(clicked(bool)), this, SLOT(slotDontSave()), Qt::UniqueConnection);
    connect(ui->buttonCancel, SIGNAL(clicked(bool)), this, SLOT(slotCancel()));
}

SaveDialog::~SaveDialog()
{
    delete ui;
}

void SaveDialog::slotSave()
{
    if(obj->mFile.fileName().isEmpty())
    {
        if(!obj->slotSaveAs())
        {
            return reject();
        }
    }
    else
    {
        saveFileFunction(obj->mFile, mData);
    }
    accept();
}

void SaveDialog::slotCancel()
{
    reject();
}

void SaveDialog::slotDontSave()
{
    accept();
}

