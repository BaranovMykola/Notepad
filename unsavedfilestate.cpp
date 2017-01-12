#include "unsavedfilestate.h"

#include "mainwindow.h"
#include "savedfilestate.h"
#include "savefilefunction.h"

#include <QDebug>

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
    saveFileFunction(obj.mFile, data);
}

void UnsavedFileState::close(MainWindow &obj)
{
    SaveDialog askSave(0, obj.mFile, obj.getPlainText());
    if(QDialog::Accepted == askSave.exec())
    {
        obj.close();
    }
}
