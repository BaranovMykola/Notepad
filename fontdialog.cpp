#include "fontdialog.h"
#include "ui_fontdialog.h"

#include <QListView>
//#include <QStringList>
//#include <QStringListModel>

#include <QListWidgetItem>
#include <QLineEdit>
#include <QPushButton>
#include <QFontDatabase>
#include <QStringList>

#include "fontmodel.h"

FontDialog::FontDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FontDialog)
{
    ui->setupUi(this);
    QFontDatabase base;
    QStringList lst = base.families();

for(auto i : lst)
{
    QWidget* wgt = new QWidget;
    QLayout* l = new QHBoxLayout;
    QLabel* customFont = new QLabel("CUSTOM LABEL DONE");
    auto font = customFont->font();
    font.setFamily(i);
    customFont->setFont(font);
    l->addWidget( customFont );
    wgt->setLayout( l );

    QListWidgetItem* item = new QListWidgetItem( ui->listWidget );
    item->setSizeHint( wgt->sizeHint() );
    ui->listWidget->setItemWidget( item, wgt );
}

}

FontDialog::~FontDialog()
{
    delete ui;
}
