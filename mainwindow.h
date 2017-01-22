#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAbstractScrollArea>
#include <QFile>
#include <memory>

#include "savedialog.h"
#include "constants.h"
#include "finddialog.h"
#include "replacedialog.h"
#include "gotodialog.h"
#include "fontdialog.h"

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
    void slotFindNext();
    void slotEditFindWord();
    void slotReplace();
    void slotGoTo();
    void slotInserData();
    void slotFont();
    void slotWordWrap();
private:
    void saveFontTo(const QString& path, const QString &file);
    void open();
    void save();
    void erase();
    void updateTitle(QString newTitle);
    QString getPlainText();
    QFont readConfig(const QString& path, const QString& file);

    QJsonObject makeJsonFont()const;

    friend class SavedFileState;
    friend class UnsavedFileState;
    friend class SaveDialog;

    class AbstractSaveFileState* stateSave;

    Ui::MainWindow *ui;
    QFile mFile;
    QString mPathFile;
    FindDialog findMenu;
    ReplaceDialog replaceMenu;
    GoToDialog mGoToMenu;
    FontDialog mFontMenu;
    bool mFontLoaded;
    QString mStyleName;

};

#endif // MAINWINDOW_H
