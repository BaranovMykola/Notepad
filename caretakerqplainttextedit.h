#ifndef CARETAKERQPLAINTTEXTEDIT_H
#define CARETAKERQPLAINTTEXTEDIT_H

#include <list>

#include "mementoqplaintextedit.h"

class CaretakerQPlaintTextEdit
{
public:
    CaretakerQPlaintTextEdit();
    void add(MementoQPlainTextEdit* newState);
    MementoQPlainTextEdit* get();
    void next();
    void prev();
    bool end()const;
    bool begin()const;
private:
    std::list<MementoQPlainTextEdit*> changes;
    std::list<MementoQPlainTextEdit*>::iterator current;
};

#endif // CARETAKERQPLAINTTEXTEDIT_H
