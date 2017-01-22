#include "savedfilestate.h"

#include "mainwindow.h"
#include "unsavedfilestate.h"

#include "ui_mainwindow.h"

SavedFileState::~SavedFileState()
{
}

void SavedFileState::updateState(MainWindow &obj)
{
    obj.stateSave = new UnsavedFileState;
    delete this;
}

void SavedFileState::save(MainWindow& obj)
{
    obj.ui->statusBar->showMessage(QString("File has been saved already (%1)").arg(obj.mFile.fileName()));
}

void SavedFileState::close(MainWindow &obj)
{
    obj.close();
}

void SavedFileState::open(MainWindow &obj)
{
    obj.open();
}

void SavedFileState::newDoc(MainWindow &obj)
{
    obj.mFile.setFileName(QString());
    obj.erase();
}
