//************************************************************************
//    This module implement setup font
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

#ifndef FONTDIALOG_H
#define FONTDIALOG_H

#include <QDialog>
#include <QFontDatabase>
#include <QListWidget>
#include <QLabel>
#include <QFont>

#include "loadingfontsdialog.h"

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
    LoadingFontsDialog loading;
    QFontDatabase base;
};

#endif // FONTDIALOG_H
