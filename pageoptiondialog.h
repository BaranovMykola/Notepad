#ifndef PAGEOPTIONDIALOG_H
#define PAGEOPTIONDIALOG_H

#include <QDialog>

namespace Ui {
class PageOptionDialog;
}

class PageOptionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PageOptionDialog(QWidget *parent = 0);
    ~PageOptionDialog();

private:
    Ui::PageOptionDialog *ui;
};

#endif // PAGEOPTIONDIALOG_H
