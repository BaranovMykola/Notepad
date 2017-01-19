#ifndef REPLACEDIALOG_H
#define REPLACEDIALOG_H

#include <QDialog>
#include "finddialog.h"

namespace Ui {
class ReplaceDialog;
}

class ReplaceDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ReplaceDialog(QWidget *parent = 0);
    ~ReplaceDialog();
    void setFindDialog(FindDialog* findMenu);
public slots:
    void slotCancel();
    bool slotFindNext();
    void slotReplace();
    void slotReplaceAll();
private:
    bool replace(bool errorReport);
    Ui::ReplaceDialog *ui;
    FindDialog* mFindMenu;
};

#endif // REPLACEDIALOG_H
