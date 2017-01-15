#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAbstractScrollArea>
#include <QFile>
#include <memory>

#include "savedialog.h"
#include "constants.h"
#include "finddialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void closeEvent(QCloseEvent *event);
public slots:
    void slotOpenFile();
    void slotNewFile();
    void slotSaveFile();
    void slotSaveAs();
    void slotClose();
    void slotEdit();
    void slotDeleteSelected();
    void slotFind();
private:
    void open();
    void save();
    void erase();
    void updateTitle(QString newTitle);
    QString getPlainText();

    friend class SavedFileState;
    friend class UnsavedFileState;
    friend class SaveDialog;

    class AbstractSaveFileState* stateSave;

    Ui::MainWindow *ui;
    QFile mFile;
    QString mPathFile;
    FindDialog findMenu;
};

#endif // MAINWINDOW_H
