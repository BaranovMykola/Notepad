#ifndef LOADINGFONTSDIALOG_H
#define LOADINGFONTSDIALOG_H

#include <QDialog>

namespace Ui {
class LoadingFontsDialog;
}

class LoadingFontsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoadingFontsDialog(QWidget *parent = 0);
    ~LoadingFontsDialog();

private:

    friend class FontDialog;

    Ui::LoadingFontsDialog *ui;
};

#endif // LOADINGFONTSDIALOG_H
