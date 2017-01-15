#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QTextDocument>
#include <QFileDialog>
#include <QTextStream>
#include <QTextCursor>
#include <iterator>

#include "abstractsavefilestate.h"
#include "unsavedfilestate.h"
#include "savedfilestate.h"
#include "savefilefunction.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    findMenu(0)
{
    stateSave = new SavedFileState;
    ui->setupUi(this);

    findMenu.setMemo(ui->memo);
//    findMenu.setMain(this);
    connect(ui->actionOpen, SIGNAL(triggered(bool)), this, SLOT(slotOpenFile()), Qt::UniqueConnection);
    connect(ui->actionSave, SIGNAL(triggered(bool)), this, SLOT(slotSaveFile()), Qt::UniqueConnection);
    connect(ui->actionExit, SIGNAL(triggered(bool)), this, SLOT(slotClose()), Qt::UniqueConnection);
    connect(ui->memo, SIGNAL(textChanged()), this, SLOT(slotEdit()), Qt::UniqueConnection);
    connect(ui->actionSave_as, SIGNAL(triggered(bool)), this, SLOT(slotSaveAs()), Qt::UniqueConnection);
    connect(ui->actionDelete, SIGNAL(triggered(bool)), this, SLOT(slotDeleteSelected()), Qt::UniqueConnection);
    connect(ui->actionFind, SIGNAL(triggered(bool)), this, SLOT(slotFind()), Qt::UniqueConnection);
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
        //event->ignore(); //prevent for closing after asking :D
        slotClose();
        if(dynamic_cast<UnsavedFileState*>(stateSave) == nullptr)
        {
            event->accept();
        }
        else
        {
            event->ignore();
        }
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
}

void MainWindow::slotSaveAs()
{
    mFile.setFileName(saveAs());
    //stateSave->save(*this);
    auto data = getPlainText();
    saveFileFunction(mFile, data);
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

void MainWindow::slotDeleteSelected()
{
    auto cursor = ui->memo->textCursor();
    cursor.removeSelectedText();
    ui->memo->setTextCursor(cursor);

}

void MainWindow::slotFind()
{
//    QString data = getPlainText();
//    int beg;
//    int end;
//    //beg = std::distance(data.)
    findMenu.show();
    findMenu.activateWindow();
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
