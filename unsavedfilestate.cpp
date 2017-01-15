#include "unsavedfilestate.h"

#include "mainwindow.h"
#include "savedfilestate.h"
#include "savefilefunction.h"

#include <QDebug>
#include <QCloseEvent>

UnsavedFileState::UnsavedFileState()
{

}

void UnsavedFileState::updateState(MainWindow &obj)
{
    obj.stateSave = new SavedFileState;
    delete this;
}

void UnsavedFileState::save(MainWindow& obj)
{
    auto data = obj.getPlainText();
    if(obj.mFile.fileName().isEmpty())
    {
        obj.mFile.setFileName(saveAs());
    }
    if(!obj.mFile.fileName().isEmpty())
    {
        saveFileFunction(obj.mFile, data);
        updateState(obj);
    }
}

void UnsavedFileState::close(MainWindow &obj)
{
    SaveDialog askSave(0, obj.mFile, obj.getPlainText());
    if(QDialog::Accepted == askSave.exec())
    {
        if(dynamic_cast<SavedFileState*>(obj.stateSave) == nullptr)
        {
            obj.stateSave->updateState(obj);
        }
        obj.close();
    }
}

void UnsavedFileState::open(MainWindow &obj)
{
    SaveDialog askSave(0, obj.mFile, obj.getPlainText());
    if(QDialog::Accepted == askSave.exec())
    {
        obj.open();
    }
}
