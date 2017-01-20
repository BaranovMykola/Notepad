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
    ~LoadingDialog();

private:

    friend class FontDialog;

    Ui::LoadingDialog *ui;
};

#endif // LOADNGDIALOG_H
