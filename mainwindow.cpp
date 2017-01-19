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
#include "ui_finddialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    findMenu(0),
    replaceMenu(0)
{
    stateSave = new SavedFileState;
    ui->setupUi(this);

    findMenu.setMemo(ui->memo);
    replaceMenu.setFindDialog(&findMenu);

    connect(ui->actionOpen, SIGNAL(triggered(bool)), this, SLOT(slotOpenFile()), Qt::UniqueConnection);
    connect(ui->actionSave, SIGNAL(triggered(bool)), this, SLOT(slotSaveFile()), Qt::UniqueConnection);
    connect(ui->actionExit, SIGNAL(triggered(bool)), this, SLOT(slotClose()), Qt::UniqueConnection);
    connect(ui->memo, SIGNAL(textChanged()), this, SLOT(slotEdit()), Qt::UniqueConnection);
    connect(ui->actionSave_as, SIGNAL(triggered(bool)), this, SLOT(slotSaveAs()), Qt::UniqueConnection);
    connect(ui->actionDelete, SIGNAL(triggered(bool)), this, SLOT(slotDeleteSelected()), Qt::UniqueConnection);
    connect(ui->actionFind, SIGNAL(triggered(bool)), this, SLOT(slotFind()), Qt::UniqueConnection);
    connect(ui->actionFind_next, SIGNAL(triggered(bool)), this, SLOT(slotFindNext()), Qt::UniqueConnection);
    connect(findMenu.ui->whatFind, SIGNAL(editingFinished()), this, SLOT(slotEditFindWord()), Qt::UniqueConnection);
    connect(ui->actionNew, SIGNAL(triggered(bool)), this, SLOT(slotNewFile()), Qt::UniqueConnection);
    connect(ui->actionReplace, SIGNAL(triggered(bool)), this, SLOT(slotReplace()), Qt::UniqueConnection);

    ui->actionOpen->setShortcut(QKeySequence::Open);
    ui->actionExit->setShortcut(QKeySequence::Close);
    ui->actionFind->setShortcut(QKeySequence::Find);
    ui->actionFind_next->setShortcut(QKeySequence::FindNext);
    ui->actionSave->setShortcut(QKeySequence::Save);
    ui->actionCopy->setShortcut(QKeySequence::Copy);
    ui->actionUndo_2->setShortcut(QKeySequence::Undo);
    ui->actionDelete->setShortcut(QKeySequence::Delete);
    ui->actionPaste->setShortcut(QKeySequence::Paste);
    ui->actionCut_2->setShortcut(QKeySequence::Cut);
    ui->actionNew->setShortcut(QKeySequence::New);
    ui->actionReplace->setShortcut(QKeySequence::Replace);

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
    stateSave->open(*this);
}

void MainWindow::slotNewFile()
{
    stateSave->newDoc(*this);
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
    ui->actionFind->setEnabled(!ui->memo->toPlainText().isEmpty());
}

void MainWindow::slotDeleteSelected()
{
    auto cursor = ui->memo->textCursor();
    cursor.removeSelectedText();
    ui->memo->setTextCursor(cursor);

}

void MainWindow::slotFind()
{
    findMenu.show();
    findMenu.activateWindow();
}

void MainWindow::slotFindNext()
{
    findMenu.slotFindNext();
}

void MainWindow::slotEditFindWord()
{
    ui->actionFind_next->setEnabled(!findMenu.ui->whatFind->text().isEmpty());
}

void MainWindow::slotReplace()
{
    replaceMenu.show();
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

void MainWindow::erase()
{
    ui->memo->clear(); //edited -> unsavedstate
    stateSave->updateState(*this); //setupp savedstate
}

void MainWindow::updateTitle(QString newTitle)
{
    setWindowTitle(newTitle+TitleSeparator+TitleName);
}

QString MainWindow::getPlainText()
{
    return ui->memo->toPlainText();
}
