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

//// \brief Some useful function for saving file

#include "savefilefunction.h"

#include <QFile>
#include <QTextStream>
#include <QString>
#include <QDir>
#include <QFileDialog>

QString saveAs()
{
    QFileDialog askFile(0, "Save as...", QDir::homePath(), "Text File (*.txt)");
    askFile.setAcceptMode(QFileDialog::AcceptSave);
    askFile.setFileMode(QFileDialog::AnyFile);
    if(askFile.exec()){
        QStringList filePath = askFile.selectedFiles();
        //filePath[0] - only one file to select is allowed;
        return filePath[0];
    }
    else
    {
        return QString();
    }
}

void saveFileFunction(QFile &file, QString& data)
{
    file.open(QIODevice::WriteOnly);
    file.seek(0);
    file.resize(0);
    QTextStream writingStream(&file);
    writingStream << data;
}

QString openFileFunction(QFile &file)
{
    if(file.open(QIODevice::ReadWrite))
    {
        QTextStream stream(&file);
        return stream.readAll();
    }
}
