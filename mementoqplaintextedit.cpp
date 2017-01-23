#include "mementoqplaintextedit.h"

MementoQPlainTextEdit::MementoQPlainTextEdit(QString _state):
    state(_state)
{

}

QString MementoQPlainTextEdit::getState() const
{
    return state;
}
