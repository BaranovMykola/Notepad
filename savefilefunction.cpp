#include "savefilefunction.h"

#include <QFile>
#include <QTextStream>
#include <QString>
#include <QDir>
#include <QFileDialog>

QString saveAs()
{
    QFileDialog askFile(0, "Open File...", QDir::homePath(), "Text File (*.txt)");
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
