#ifndef FONTDIALOG_H
#define FONTDIALOG_H

#include <QDialog>
#include <QFontDatabase>
#include <QListWidget>
#include <QLabel>
#include <QFont>

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
    QFont getFont();
    void updateSelectedFonts(QFont currentFont, QString style);
public slots:
    void slotFamily();
    void slotUpdateExample();
    void slotMoreFonts();
private:

    friend class MainWindow;

    void populateFonts();
    void populateStyles(QString family, QString oldStyle, int oldSize);
    void populateSize(QString family, QString style, int oldSize);
    QLabel* getSelectedLabel(QListWidget *list);
    int getSelectedSize();

    Ui::FontDialog *ui;
    LoadingDialog loading;
    QFontDatabase base;
};

#endif // FONTDIALOG_H
