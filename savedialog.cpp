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

SaveDialog::SaveDialog(QWidget *parent, QFile &file, QString data) :
    QDialog(parent),
    ui(new Ui::SaveDialog),
    mFile(file),
    mData(data)
{
    ui->setupUi(this);
    this->setWindowFlags(this->windowFlags() | Qt::MSWindowsFixedSizeDialogHint);
    QPalette sample_palette;
    sample_palette.setColor(QPalette::Window, Qt::white);
    sample_palette.setColor(QPalette::WindowText, QColor(0,80,170));
    auto filePath = mFile.fileName();
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
    if(mFile.fileName().isEmpty())
    {
        mFile.setFileName(saveAs());
    }
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

