//Copyright (C) 2017  Baranov Mykola

//This program is free software: you can redistribute it and/or modify
//it under the terms of the GNU General Public License as published by
//the Free Software Foundation, either version 3 of the License, or
//(at your option) any later version.

//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.

//You should have received a copy of the GNU General Public License
//along with this program.  If not, see http://www.gnu.org/licenses/

//// \brief Pattern state. Responds for behaviour unsaved file

#include "unsavedfilestate.h"

#include "mainwindow.h"
#include "savedfilestate.h"
#include "savefilefunction.h"

#include <QDebug>
#include <QCloseEvent>

#include "ui_mainwindow.h"

UnsavedFileState::~UnsavedFileState()
{

}

void UnsavedFileState::updateState(MainWindow &obj)
{
    obj.stateSave = new SavedFileState;
    delete this;
}

void UnsavedFileState::save(MainWindow& obj)
{
    auto data = obj.getPlainText();
    if(obj.mFile.fileName().isEmpty())
    {
        obj.slotSaveAs();
    }
    else
    {
        saveFileFunction(obj.mFile, data);
        updateState(obj);
    }
    obj.ui->statusBar->showMessage(QString("File saved as %1").arg(obj.mFile.fileName()));
}

void UnsavedFileState::close(MainWindow &obj)
{
    SaveDialog askSave(0, &obj, obj.getPlainText());
    if(QDialog::Accepted == askSave.exec())
    {
        if(dynamic_cast<SavedFileState*>(obj.stateSave) == nullptr)
        {
            obj.stateSave->updateState(obj);
        }
        obj.close();
    }
}

void UnsavedFileState::open(MainWindow &obj)
{
    SaveDialog askSave(0, &obj, obj.getPlainText());
    if(QDialog::Accepted == askSave.exec())
    {
        obj.open();
    }
}

void UnsavedFileState::newDoc(MainWindow &obj)
{
    SaveDialog askSave(0, &obj, obj.getPlainText());
    if(QDialog::Accepted == askSave.exec())
    {
        obj.mFile.setFileName(QString());
        obj.erase();
        obj.ui->statusBar->showMessage(QString("Prepeared new file"));
    }
}
