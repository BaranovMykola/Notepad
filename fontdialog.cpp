#include "fontdialog.h"
#include "ui_fontdialog.h"

#include <QListView>
#include <QListWidgetItem>
#include <QLineEdit>
#include <QPushButton>
#include <QFontDatabase>
#include <QStringList>
#include <QProgressBar>
#include <QTimer>
#include <QThread>
#include <QtConcurrent/QtConcurrent>

#include <iterator>

#include "ui_loadngdialog.h"

FontDialog::FontDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FontDialog)
{
    ui->setupUi(this);

    connect(ui->fontList, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(slotFamily()), Qt::UniqueConnection);
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
}

void FontDialog::populateFonts()
{
    QFontDatabase base;
    QStringList lst = base.families();

    loading.show();
    loading.ui->progressBar->setRange(0, std::distance(lst.begin(), lst.end()));

    int iteration = 0;
    for(auto i : lst)
    {
        loading.ui->progressBar->setValue(++iteration);
        QCoreApplication::processEvents(QEventLoop::AllEvents, 0);
        QWidget* widget = new QWidget;
        QLayout* box = new QHBoxLayout;
        QLabel* customFont = new QLabel(i);
        auto font = customFont->font();
        font.setFamily(i);
        customFont->setFont(font);
        box->addWidget(customFont);
        widget->setLayout(box);
        QListWidgetItem* item = new QListWidgetItem( ui->fontList );
        item->setSizeHint(widget->sizeHint());
        ui->fontList->setItemWidget(item, customFont);
    }
    loading.close();
}
