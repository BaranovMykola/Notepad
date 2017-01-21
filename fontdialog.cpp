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

#include <iterator>

#include "constants.h"

#include "ui_loadngdialog.h"

FontDialog::FontDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FontDialog)
{
    ui->setupUi(this);

    connect(ui->fontList, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(slotFamily()), Qt::UniqueConnection);
    connect(ui->sizeList, SIGNAL(clicked(QModelIndex)), this, SLOT(slotSize()), Qt::UniqueConnection);

    connect(ui->fontList, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(slotUpdateExample()), Qt::UniqueConnection);
    connect(ui->styleList, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(slotUpdateExample()), Qt::UniqueConnection);
    connect(ui->sizeList, SIGNAL(clicked(QModelIndex)), this, SLOT(slotUpdateExample()), Qt::UniqueConnection);
}

FontDialog::~FontDialog()
{
    delete ui;
}

void FontDialog::slotFamily()
{
    populateStyles(getSelectedLabel(ui->fontList)->text()); //call only after clicked -> always selected
}

void FontDialog::slotStyle()
{
    populateStyles(getSelectedLabel(ui->styleList)->text());
}

void FontDialog::slotSize()
{

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
    loading.close();
}

void FontDialog::populateStyles(QString family)
{
    QLabel* oldStyle = getSelectedLabel(ui->styleList);
    QString findString;
    bool restored = false;
    if(oldStyle != nullptr)
    {
        findString = oldStyle->text();
    }
    QStringList lst = base.styles(family);
    ui->styleList->clear();
    int index = 0;
    for(auto i : lst)
    {
        QLabel* newItem = new QLabel(i);
        newItem->setFont(base.font(family, i, DefaultFontSize));
        QListWidgetItem* item = new QListWidgetItem(ui->styleList);
        ui->styleList->setItemWidget(item, newItem);
        if(newItem->text() == findString && oldStyle != nullptr)
        {
            restored = true;
            ui->styleList->setCurrentItem( ui->styleList->item(ui->styleList->count()-1));
        }

    }
    if(!restored && ui->styleList->count() > 0)
    {
        ui->styleList->setCurrentRow(0);
    }
    populateSize(family, getSelectedLabel(ui->styleList)->text());
}

void FontDialog::populateSize(QString family, QString style)
{
    int oldSize = getSelectedSize();
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
//    modelIndex.r
    ui->sizeList->setCurrentIndex(modelIndex);
    slotUpdateExample();

}

QLabel* FontDialog::getSelectedLabel(QListWidget* list)
{
    QListWidgetItem* item = list->currentItem();
    return dynamic_cast<QLabel*>(list->itemWidget(item));
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
