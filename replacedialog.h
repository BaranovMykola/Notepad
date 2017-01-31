//************************************************************************
//    This module implement repalcing word using FindDialog
//
//    Copyright (C) 2017 Baranov Mykola <mapsg32@gmail.com>
//
//    This program is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.

//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.

//    You should have received a copy of the GNU General Public License
//    along with this program.  If not, see <http://www.gnu.org/licenses/>
//************************************************************************

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
    void slotEditRepalceWord();
private:
    bool replace(bool errorReport);
    Ui::ReplaceDialog *ui;
    FindDialog* mFindMenu;
};

#endif // REPLACEDIALOG_H
