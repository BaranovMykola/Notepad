#ifndef SAVEFILEFUNCTION_H
#define SAVEFILEFUNCTION_H

class QFile;
class QString;

QString saveAs();

void saveFileFunction(QFile& file, QString& data);
QString openFileFunction(QFile& file);

#endif // SAVEFILEFUNCTION_H
