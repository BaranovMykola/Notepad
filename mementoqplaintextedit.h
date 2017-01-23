#ifndef MEMENTOQPLAINTEXTEDIT_H
#define MEMENTOQPLAINTEXTEDIT_H

#include <QString>

class MementoQPlainTextEdit
{
public:
    MementoQPlainTextEdit(QString _state);
    QString getState()const;
private:
    QString state;
};

#endif // MEMENTOQPLAINTEXTEDIT_H
