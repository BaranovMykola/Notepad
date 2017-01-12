#ifndef SAVEFILEFUNCTION_H
#define SAVEFILEFUNCTION_H

class QFile;
class QString;

QString saveAs();

void saveFileFunction(QFile& file, QString& data);

#endif // SAVEFILEFUNCTION_H
