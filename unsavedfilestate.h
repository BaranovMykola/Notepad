#ifndef UNSAVEDFILESTATE_H
#define UNSAVEDFILESTATE_H

#include "abstractsavefilestate.h"

class UnsavedFileState : public AbstractSaveFileState
{
public:
    UnsavedFileState();
    void updateState(MainWindow &obj);
    void save(MainWindow& obj);
    void close(MainWindow &obj);
    void open(MainWindow &obj);
    void newDoc(MainWindow &obj);
private:
};

#endif // UNSAVEDFILESTATE_H
