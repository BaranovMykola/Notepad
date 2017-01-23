#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAbstractScrollArea>
#include <QFile>
#include <memory>
#include <tuple>
#include <QJsonValue>

#include "savedialog.h"
#include "constants.h"
#include "finddialog.h"
#include "replacedialog.h"
#include "gotodialog.h"
#include "fontdialog.h"
#include "aboutdialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    enum DataType{String, Double, Bool};
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
    void slotStatusBar();
    void slotAbout();
private:
    void open();
    void save();
    void erase();
    void updateTitle(QString newTitle);
    QString getPlainText();

    void readConfigFrom(const QString& path, const QString &file);

    std::tuple<std::map<QString, QString>, std::map<QString, double>, std::map<QString, bool> > readQJsonObject(QJsonObject obj)const;

    QFont readFont(QJsonObject fontObject);
    bool readWordWrap(QJsonObject obj)const;
    bool readStatusBar(QJsonObject obj)const;

    QJsonObject makeJsonFont()const;
    QJsonObject makeJsonWordWrap()const;
    QJsonObject makeJsonStatusBar()const;

    QJsonObject makeGenerealJsonObject();

    void saveConfigTo(const QString& path, const QString &file);
    void writeJsonConfig(QFile& config);

    MainWindow::DataType getTypeData(QJsonValueRef value);


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
    AboutDialog mAboutMenu;
    bool mFontLoaded;
    QString mStyleName;

};

#endif // MAINWINDOW_H
