#ifndef SAVEDIALOG_H
#define SAVEDIALOG_H

#include <QDialog>

class MainWindow;
class QFile;

namespace Ui {
class SaveDialog;
}

class SaveDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SaveDialog(QWidget *parent, MainWindow* _obj, QString data);
    ~SaveDialog();
public slots:
    void slotSave();
    void slotDontSave();
    void slotCancel();

private:
    Ui::SaveDialog *ui;
    MainWindow* obj;
    QString mData;
};

#endif // SAVEDIALOG_H
