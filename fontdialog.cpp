#include "fontdialog.h"
#include "ui_fontdialog.h"

#include <QListView>
//#include <QStringList>
//#include <QStringListModel>

#include "fontmodel.h"

FontDialog::FontDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FontDialog)
{
    ui->setupUi(this);
    QStringList lst;
//    QStringListModel* m = new QStringListModel;
    QStringListModel* m = new QStringListModel;
    lst << "abc" << "ABC" << "???";
    m->setStringList(lst);
    ui->listView->setModel(m);
}

FontDialog::~FontDialog()
{
    delete ui;
}
