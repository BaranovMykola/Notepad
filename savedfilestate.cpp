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

//// \brief Pattern state. Responds for behaviour of saved document.

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
    QString fileName = obj.mFile.fileName();
    if(fileName.isEmpty())
    {
        fileName = "Untitled";
    }
    obj.ui->statusBar->showMessage(QString("File has been saved already (%1)").arg(fileName));
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
