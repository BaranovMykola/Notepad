#ifndef SAVEDFILESTATE_H
#define SAVEDFILESTATE_H

#include "abstractsavefilestate.h"

class SavedFileState : public AbstractSaveFileState
{
public:
    SavedFileState();
    void updateState(MainWindow& obj);
    void save(MainWindow& obj);
    void close(MainWindow& obj);
    void open(MainWindow &obj);
private:
};

#endif // SAVEDFILESTATE_H
