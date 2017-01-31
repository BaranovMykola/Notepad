//************************************************************************
//    This module implement find dialog with algorithm
//
//    Copyright (C) 2017 Baranov Mykola
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

#ifndef FINDDIALOG_H
#define FINDDIALOG_H

#include <QDialog>
#include <QTextCursor>
#include <QLineEdit>

//#include "finddialog.h"
#include "constants.h"

class QPlainTextEdit;
class MainWindow;

namespace Ui {
class FindDialog;
}


class FindDialog : public QDialog
{
    Q_OBJECT

public:
    enum Direction{Up, Down};

    explicit FindDialog(QWidget *parent = 0);
    ~FindDialog();
    void setMemo(QPlainTextEdit* _memo);
public slots:
    void slotCancel();
    void slotFindNext();
private:
    bool findNext(QString subject, Direction type, bool matchCase = false, bool errorReport = false);
    void errorMessage(QString subject, QString message = NotFoundMessage);
    void selectText(int from, int to, QTextCursor& pointer);

    friend class MainWindow;
    friend class ReplaceDialog;

    Ui::FindDialog *ui;
    QPlainTextEdit* memo;
};

#endif // FINDDIALOG_H
