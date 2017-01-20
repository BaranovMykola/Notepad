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
//    connect(ui->fontList, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(slotUpdateExample()), Qt::UniqueConnection);
//    connect(ui->styleList, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(slotUpdateExample()), Qt::UniqueConnection);
}

FontDialog::~FontDialog()
{
    delete ui;
}

void FontDialog::slotFamily()
{
    QListWidgetItem* item = ui->fontList->currentItem();
    QLabel* selectedLabel = dynamic_cast<QLabel*>(ui->fontList->itemWidget(item));
    ui->example->setFont(selectedLabel->font());
    populateStyles(selectedLabel->text());
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
    QStringList lst = base.styles(family);
    ui->styleList->clear();
    for(auto i : lst)
    {
        QLabel* newItem = new QLabel(i);
        newItem->setFont(base.font(family, i, DefaultFontSize));
        QListWidgetItem* item = new QListWidgetItem(ui->styleList);
        ui->styleList->setItemWidget(item, newItem);

    }
    populateSize(family, "Normal");
}

void FontDialog::populateSize(QString family, QString style)
{
    auto lst = base.pointSizes(family, style);
    QStringList pointTextList;
    for(auto i : lst)
    {
        pointTextList.append(QString::number(i));
    }
    QStringListModel* model = new QStringListModel;
    model->setStringList(pointTextList);
    ui->sizeList->setModel(model);
    slotUpdateExample();

}

void FontDialog::slotUpdateExample()
{

}
