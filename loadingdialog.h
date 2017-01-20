#ifndef LOADNGDIALOG_H
#define LOADNGDIALOG_H

#include <QDialog>
#include <QProgressBar>


namespace Ui {
class LoadingDialog;
}


class LoadingDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoadingDialog(QWidget *parent = 0);
    void setRange(int from, int to);
    void setValue(int value);
    ~LoadingDialog();

private:

    friend class FontDialog;

    Ui::LoadingDialog *ui;
};

#endif // LOADNGDIALOG_H
