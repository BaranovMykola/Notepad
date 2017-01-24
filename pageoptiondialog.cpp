#include "pageoptiondialog.h"
#include "ui_pageoptiondialog.h"

#include <QPrinterInfo>
#include <QDebug>
#include <QPainter>
#include <QPrintPreviewDialog>

void PageOptionDialog::setPrinter(QPrinter *_printer)
{
    printer = _printer;
}

PageOptionDialog::PageOptionDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PageOptionDialog),
    pageSizes(new std::map<QString, QPageSize>)
{
    ui->setupUi(this);

}

PageOptionDialog::~PageOptionDialog()
{
    delete ui;
}

void PageOptionDialog::slotSize()
{
//    auto current = ui->sizeComboBox->currentText();
//    QPageSize ps = (*pageSizes)[current];
//    const int k = 10;
//    qDebug() << ps.sizePoints().width()/k << ps.sizePoints().height()/k;
//    QPixmap myPix( QSize(ui->preview->size()) );
//    QPainter painter(&myPix);
//    myPix.fill(QColor("white"));
//    painter.setBrush( Qt::red );
//    painter.drawRect(0,0, ps.sizePoints().width()/k, ps.sizePoints().height()/k);

//    label = new QLabel("", this);
//    ui->example->setPixmap(myPix);
    QPrintPreviewDialog preview(printer, this);
    preview.exec();
}

void PageOptionDialog::populatePagesize()
{
    QPrinterInfo info(*printer);
    QList<QPageSize> sizes = info.supportedPageSizes();
    for(auto i : sizes)
    {
        (*pageSizes)[i.name()] = i;
        ui->sizeComboBox->insertItem(ui->sizeComboBox->count()-1, i.name());
    }
    connect(ui->sizeComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(slotSize()), Qt::UniqueConnection);
}
