#ifndef FINDDIALOG_H
#define FINDDIALOG_H

#include <QDialog>
class QPlainTextEdit;
class MainWindow;

namespace Ui {
class FindDialog;
}

class FindDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FindDialog(QWidget *parent = 0);
    ~FindDialog();
    void setMemo(QPlainTextEdit* _memo);
public slots:
    void slotCancel();
    void slotFindNext();
private:
    void errorMessage(QString subject);
    void selectText(int from, int to);
    template<typename Iter, typename IterStr, typename Result>
    Result searchNext(Iter from, Iter to, IterStr fromStr, IterStr toStr);

    Ui::FindDialog *ui;
    QPlainTextEdit* memo;
};

#endif // FINDDIALOG_H
