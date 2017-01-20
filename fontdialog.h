#ifndef FONTDIALOG_H
#define FONTDIALOG_H

#include <QDialog>

#include "loadingdialog.h"

namespace Ui {
class FontDialog;
}

class FontDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FontDialog(QWidget *parent = 0);
    ~FontDialog();
public slots:
    void slotFamily();
private:

    friend class MainWindow;

    void populateFonts();

    Ui::FontDialog *ui;
    LoadingDialog loading;
};

#endif // FONTDIALOG_H
