//************************************************************************
//    This module implement progress bar and canbe using anywhere
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
