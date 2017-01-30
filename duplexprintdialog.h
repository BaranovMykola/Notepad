#ifndef DUPLEXPRINTDIALOG_H
#define DUPLEXPRINTDIALOG_H

#include <QDialog>

namespace Ui {
class DuplexPrintDialog;
}

class DuplexPrintDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DuplexPrintDialog(QWidget *parent = 0);
    ~DuplexPrintDialog();

private:
    Ui::DuplexPrintDialog *ui;
};

#endif // DUPLEXPRINTDIALOG_H
