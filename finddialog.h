#ifndef FINDDIALOG_H
#define FINDDIALOG_H

#include <QDialog>
#include <QTextCursor>
class QPlainTextEdit;

namespace Ui {
class FindDialog;
}

class FindDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FindDialog(QWidget *parent = 0);
    ~FindDialog();
    void setMemo(QPlainTextEdit* memo);
public slots:
    void slotCancel();
//    void slotFindNext();
private:
//    void updateCursor();
    Ui::FindDialog *ui;
    QPlainTextEdit* mMemo;
//    QTextCursor mCurrent;
};

#endif // FINDDIALOG_H
