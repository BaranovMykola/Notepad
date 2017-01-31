//************************************************************************
//    This module implement asking to save file before closing
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

#ifndef SAVEDIALOG_H
#define SAVEDIALOG_H

#include <QDialog>

class MainWindow;
class QFile;

namespace Ui {
class SaveDialog;
}

class SaveDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SaveDialog(QWidget *parent, MainWindow* _obj, QString data);
    ~SaveDialog();
public slots:
    void slotSave();
    void slotDontSave();
    void slotCancel();

private:
    Ui::SaveDialog *ui;
    MainWindow* obj;
    QString mData;
};

#endif // SAVEDIALOG_H
