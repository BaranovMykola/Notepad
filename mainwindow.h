#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAbstractScrollArea>
#include <QFile>
#include <memory>
#include <tuple>
#include <QJsonValue>
#include <QtPrintSupport/QPrinter>

#include "savedialog.h"
#include "constants.h"
#include "finddialog.h"
#include "replacedialog.h"
#include "gotodialog.h"
#include "fontdialog.h"
#include "aboutdialog.h"
#include "pageoptiondialog.h"
#include <map>

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

    /*General method of reading saved data*/
    void readConfigFrom(const QString& path, const QString &file);
    /*Save all properties to *.json file*/
    void saveConfigTo(const QString& path, const QString &file);

    void openFile(QString fileName);

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
    void slotPageOption();
    void slotPrint();
private slots:
    void printFile(QPrinter* p);
private:
    void open();
    void save();
    void erase();
    void updateTitle(QString newTitle);
    QString getPlainText();


    /*General algorithm of readint QJsonObject data*/
    std::tuple<std::map<QString, QString>, std::map<QString, double>, std::map<QString, bool> > readQJsonObject(QJsonObject obj)const;

    /*Read QJsonObject pf every prperties and returns this properties*/
    QFont readFont(QJsonObject fontObject);
    bool readWordWrap(QJsonObject obj)const;
    bool readStatusBar(QJsonObject obj)const;

    /*Make QJsonObject of every properties*/
    QJsonObject makeJsonFont()const;
    QJsonObject makeJsonWordWrap()const;
    QJsonObject makeJsonStatusBar()const;

    /*Make QJsonObject of all properties*/
    QJsonObject makeGenerealJsonObject();

    void writeJsonConfig(QFile& config);

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
    QPrinter printer;
    PageOptionDialog mPageOptionMenu;

};

#endif // MAINWINDOW_H
