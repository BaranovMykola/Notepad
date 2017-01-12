#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QTextDocument>
#include <QFileDialog>
#include <QTextStream>

#include "abstractsavefilestate.h"
#include "unsavedfilestate.h"
#include "savedfilestate.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    stateSave = new SavedFileState;
    ui->setupUi(this);
    connect(ui->actionOpen, SIGNAL(triggered(bool)), this, SLOT(slotOpenFile()), Qt::UniqueConnection);
    connect(ui->actionSave, SIGNAL(triggered(bool)), this, SLOT(slotSaveFile()), Qt::UniqueConnection);
    connect(ui->actionExit, SIGNAL(triggered(bool)), this, SLOT(slotClose()), Qt::UniqueConnection);
    connect(ui->memo, SIGNAL(textChanged()), this, SLOT(slotEdit()), Qt::UniqueConnection);
    ui->actionOpen->setShortcut(QKeySequence::Open);
    ui->actionExit->setShortcut(QKeySequence::Close);
    ui->actionSave->setShortcut(QKeySequence::Save);

}

MainWindow::~MainWindow()
{
    delete ui;
    delete stateSave;
}

void MainWindow::closeEvent(QCloseEvent* event)
{
    qDebug() << "state saved: " << (dynamic_cast<UnsavedFileState*>(stateSave) == nullptr);
    if(dynamic_cast<UnsavedFileState*>(stateSave) == nullptr)
    {
        event->accept();
    }
    else
    {
        event->ignore();
        slotClose();
    }
}

void MainWindow::slotOpenFile()
{
    stateSave->save(*this);
    open();
}

void MainWindow::slotSaveFile()
{
    stateSave->save(*this);
    stateSave->updateState(*this);
}

void MainWindow::slotClose()
{
    stateSave->close(*this);
}

void MainWindow::slotEdit()
{
    if(dynamic_cast<UnsavedFileState*>(stateSave) == nullptr)
    {   //if document saved
        stateSave->updateState(*this);
        qDebug() << "edited";
    }
}

void MainWindow::open()
{
    QFileDialog files;
    mPathFile = QFileDialog::getOpenFileName(this, tr("Open File..."), QDir::homePath(), "Text Files (*.txt);; All Files (*.*)");
    if(!mPathFile.isEmpty())
    {
        mFile.setFileName(mPathFile);
        if(mFile.open(QIODevice::ReadWrite))
        {
            QTextStream stream(&mFile);
            QString data = stream.readAll();
            ui->memo->setPlainText(data);
            updateTitle(mPathFile);
        }
    }
}

void MainWindow::save()
{


    //mFile.write(arr);
}

void MainWindow::updateTitle(QString newTitle)
{
    setWindowTitle(newTitle+TitleSeparator+TitleName);
}

QString MainWindow::getPlainText()
{
    return ui->memo->toPlainText();
}
