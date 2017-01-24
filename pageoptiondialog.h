#ifndef PAGEOPTIONDIALOG_H
#define PAGEOPTIONDIALOG_H

#include <QDialog>
#include <map>
#include <QPageSize>
#include <map>
#include <memory>
#include <QPrinter>

namespace Ui {
class PageOptionDialog;
}

class PageOptionDialog : public QDialog
{
    Q_OBJECT
    void setPrinter(QPrinter* _printer);
public:
    explicit PageOptionDialog(QWidget *parent = 0);
    ~PageOptionDialog();
public slots:
    void slotSize();
private:
    void populatePagesize();
    QPrinter* printer;

    friend class MainWindow;

    Ui::PageOptionDialog *ui;
    std::unique_ptr<std::map<QString, QPageSize>> pageSizes;

};

#endif // PAGEOPTIONDIALOG_H
