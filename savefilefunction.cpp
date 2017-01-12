#include "savefilefunction.h"

#include <QFile>
#include <QTextStream>
#include <QString>

void saveFileFunction(QFile &file, QString& data)
{
    file.seek(0);
    file.resize(0);
    QTextStream writingStream(&file);
    writingStream << data;
}
