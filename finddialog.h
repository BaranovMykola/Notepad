#ifndef FINDDIALOG_H
#define FINDDIALOG_H

#include <QDialog>
#include <QTextCursor>
#include <QLineEdit>

//#include "finddialog.h"
#include "constants.h"

class QPlainTextEdit;
class MainWindow;

namespace Ui {
class FindDialog;
}


class FindDialog : public QDialog
{
    Q_OBJECT

public:
    enum Direction{Up, Down};

    explicit FindDialog(QWidget *parent = 0);
    ~FindDialog();
    void setMemo(QPlainTextEdit* _memo);
public slots:
    void slotCancel();
    void slotFindNext();
private:
    bool findNext(QString subject, Direction type, bool matchCase = false, bool errorReport = false);
    void errorMessage(QString subject, QString message = NotFoundMessage);
    void selectText(int from, int to, QTextCursor& pointer);

    friend class MainWindow;
    friend class ReplaceDialog;

    Ui::FindDialog *ui;
    QPlainTextEdit* memo;
};

#endif // FINDDIALOG_H
