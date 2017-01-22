//Copyright (C) 2017  Baranov Mykola

//This program is free software: you can redistribute it and/or modify
//it under the terms of the GNU General Public License as published by
//the Free Software Foundation, either version 3 of the License, or
//(at your option) any later version.

//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.

//You should have received a copy of the GNU General Public License
//along with this program.  If not, see http://www.gnu.org/licenses/

//// \brief This code responds for selection fonts and sending font to MainWindow

#include "fontdialog.h"
#include "ui_fontdialog.h"

#include <QListView>
#include <QListWidgetItem>
#include <QLineEdit>
#include <QPushButton>
#include <QStringList>
#include <QProgressBar>
#include <QTimer>
#include <QThread>
#include <QtConcurrent/QtConcurrent>
#include <QProcess>

#include <iterator>

#include "constants.h"

#include "ui_loadngdialog.h"

FontDialog::FontDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FontDialog)
{
    ui->setupUi(this);

    this->setWindowFlags(this->windowFlags() | Qt::MSWindowsFixedSizeDialogHint | Qt::WindowStaysOnTopHint);

    connect(ui->fontList, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(slotFamily()), Qt::UniqueConnection);
    connect(ui->styleList, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(slotUpdateExample()), Qt::UniqueConnection);
    connect(ui->sizeList, SIGNAL(clicked(QModelIndex)), this, SLOT(slotUpdateExample()), Qt::UniqueConnection);
    connect(ui->linkFont, SIGNAL(linkActivated(QString)), this, SLOT(slotMoreFonts()), Qt::UniqueConnection);
}

FontDialog::~FontDialog()
{
    delete ui;
}

QFont FontDialog::getFont()
{
    return base.font(getSelectedLabel(ui->fontList)->text(), getSelectedLabel(ui->styleList)->text(), getSelectedSize());
}

void FontDialog::updateSelectedFonts(QFont currentFont, QString style)
{
    QFontInfo info(currentFont);
    int i;
    for(i = ui->fontList->count()-1;i>=0;--i)
    {
        ui->fontList->setCurrentRow(i);
        if(getSelectedLabel(ui->fontList)->text() == info.family())
        {
            populateStyles(getSelectedLabel(ui->fontList)->text(), style, info.pointSize());
            break;
        }
    }
}

void FontDialog::slotFamily()
{
    QString oldStyle;
    QLabel* oldLabel = getSelectedLabel(ui->styleList);
    if(oldLabel != nullptr)
    {
        oldStyle = oldLabel->text();
    }
    populateStyles(getSelectedLabel(ui->fontList)->text(), oldStyle, getSelectedSize()); //call only after clicked -> always selected
}

void FontDialog::populateFonts()
{
    QStringList lst = base.families();

    loading.show();
    loading.ui->progressBar->setRange(0, std::distance(lst.begin(), lst.end()));
    int iteration = 0;
    for(auto i : lst)
    {
        loading.ui->progressBar->setValue(++iteration);
        QCoreApplication::processEvents(QEventLoop::AllEvents, 0);
        QLabel* customFont = new QLabel(i);
        auto font = customFont->font();
        font.setFamily(i);
        customFont->setFont(base.font(i, "Normal", DefaultFontSize));
        QListWidgetItem* item = new QListWidgetItem( ui->fontList );
        ui->fontList->setItemWidget(item, customFont);
    }
    ui->fontList->setCurrentRow(0);
    loading.close();
}

void FontDialog::populateStyles(QString family, QString oldStyle, int oldSize)
{
    bool restored = false;
    QStringList lst = base.styles(family);
    ui->styleList->clear();
    for(auto i : lst)
    {
        QLabel* newItem = new QLabel(i);
        newItem->setFont(base.font(family, i, DefaultFontSize));
        QListWidgetItem* item = new QListWidgetItem(ui->styleList);
        ui->styleList->setItemWidget(item, newItem);
        if(newItem->text() == oldStyle && oldStyle != nullptr)
        {
            restored = true;
            ui->styleList->setCurrentItem( ui->styleList->item(ui->styleList->count()-1));
        }
    }
    if(!restored && ui->styleList->count() > 0)
    {
        ui->styleList->setCurrentRow(0);
    }
    populateSize(family, getSelectedLabel(ui->styleList)->text(), oldSize);
}

void FontDialog::populateSize(QString family, QString style, int oldSize)
{
    auto lst = base.pointSizes(family, style);
    QStringList pointTextList;
    int index = 0;
    bool founded = false;
    for(auto i : lst)
    {
        if(i == oldSize)
        {
            founded = true;
        }
        if(!founded)
        {
            ++index;
        }
        pointTextList.append(QString::number(i));
    }
    QStringListModel* model = new QStringListModel;
    model->setStringList(pointTextList);
    ui->sizeList->setModel(model);
    QModelIndex modelIndex = model->index(index);
    ui->sizeList->setCurrentIndex(modelIndex);
    slotUpdateExample();
}

QLabel* FontDialog::getSelectedLabel(QListWidget* list)
{
    QListWidgetItem* item = list->currentItem();
    if(item != nullptr)
    {
        return dynamic_cast<QLabel*>(list->itemWidget(item));
    }
    return nullptr;
}

int FontDialog::getSelectedSize()
{
    int size = DefaultFontSize;
    auto model = ui->sizeList->model();
    if(model != nullptr)
    {
        QModelIndexList indexes = ui->sizeList->selectionModel()->selectedIndexes();
        for(auto i : indexes)
        {
            size = i.data().toInt();
        }
    }
    return size;
}

void FontDialog::slotUpdateExample()
{
    QLabel* fontLabel = getSelectedLabel(ui->fontList);
    QLabel* styleLabel = getSelectedLabel(ui->styleList);

    int size = getSelectedSize();

    QString fontName;
    QString styleName;

    if(fontLabel != nullptr)
    {
        fontName = fontLabel->text();
    }
    if(styleLabel != nullptr)
    {
        styleName = styleLabel->text();
    }
    if(!fontName.isEmpty() && !styleName.isEmpty())
    {
        ui->example->setFont(base.font(fontLabel->text(), styleLabel->text(), size));
    }
}

void FontDialog::slotMoreFonts()
{
    std::system("control fonts");
}
