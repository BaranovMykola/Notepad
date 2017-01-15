#ifndef ABSTRACTFILESTATE_H
#define ABSTRACTFILESTATE_H

class MainWindow;

class AbstractSaveFileState
{
public:
    virtual void updateState(MainWindow& obj)=0;
    virtual void save(MainWindow& obj)=0;
    virtual void close(MainWindow& obj)=0;
    virtual void open(MainWindow& obj)=0;
private:
};

#endif // ABSTRACTFILESTATE_H
