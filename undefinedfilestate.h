#ifndef UNDEFINEDFILESTATE_H
#define UNDEFINEDFILESTATE_H

#include "abstractsavefilestate.h"

class UndefinedFileState : public AbstractSaveFileState
{
public:
    UndefinedFileState();
    void updateState(MainWindow &obj);
    bool save();
private:
};

#endif // UNDEFINEDFILESTATE_H
