#include "savedialog.h"
#include "ui_savedialog.h"

#include <QDebug>
#include <QFile>

#include "savefilefunction.h"

SaveDialog::SaveDialog(QWidget *parent, QFile &file, QString data) :
    QDialog(parent),
    ui(new Ui::SaveDialog),
    mFile(file),
    mData(data)
{
    qDebug() << "constructor";
    ui->setupUi(this);
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
    saveFileFunction(mFile, mData);
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

