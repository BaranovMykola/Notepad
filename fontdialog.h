#ifndef FONTDIALOG_H
#define FONTDIALOG_H

#include <QDialog>
#include <QFontDatabase>
#include <QListWidget>
#include <QLabel>

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
    void slotStyle();
    void slotSize();
    void slotUpdateExample();
private:

    friend class MainWindow;

    void populateFonts();
    void populateStyles(QString family);
    void populateSize(QString family, QString style);
    QLabel* getSelectedLabel(QListWidget *list);
    int getSelectedSize();

    Ui::FontDialog *ui;
    LoadingDialog loading;
    QFontDatabase base;
};

#endif // FONTDIALOG_H
