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

#include "ui_fontdialog.h"

FontDialog::FontDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FontDialog)
{
    ui->setupUi(this);

//    populateFont();


}

FontDialog::~FontDialog()
{
    delete ui;
}

void FontDialog::populateFont()
{
    QFontDatabase base;
    QStringList lst = base.families();
    loading.show();
    loading.setRange(0, std::distance(lst.begin(), lst.end()));
    int value = 0;
    for(auto i : lst)
    {
        loading.setValue(++value);
        updateProgressBar(value);
        QCoreApplication::processEvents(QEventLoop::AllEvents, 0);
        QWidget* wgt = new QWidget;
        QLayout* l = new QHBoxLayout;
        QLabel* customFont = new QLabel(i);
        auto font = customFont->font();
        font.setFamily(i);
        customFont->setFont(font);
        l->addWidget( customFont );
        wgt->setLayout( l );

        QListWidgetItem* item = new QListWidgetItem( ui->fontList );
        item->setSizeHint( wgt->sizeHint() );
        ui->fontList->setItemWidget( item, wgt );
    }
    loading.close();
}

void FontDialog::updateProgressBar(int value)
{
    loading.setValue(value);
}
