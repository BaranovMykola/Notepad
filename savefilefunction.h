#ifndef SAVEFILEFUNCTION_H
#define SAVEFILEFUNCTION_H

class QFile;
class QString;

#include <QDir>

QString saveAs(QString path = QDir::homePath());

void saveFileFunction(QFile& file, QString& data);
QString openFileFunction(QFile& file);

#endif // SAVEFILEFUNCTION_H
