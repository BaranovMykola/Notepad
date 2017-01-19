
//#ifndef QSTRINGLISTMODEL_H
//#define QSTRINGLISTMODEL_H

#include <QLabel>
#include <qstringlist.h>
#include <QAbstractListModel>
#include <qabstractitemview.h>

//QT_BEGIN_HEADER

//QT_BEGIN_NAMESPACE

//QT_MODULE(Gui)

//#ifndef QT_NO_STRINGLISTMODEL

class /*Q_GUI_EXPORT*/ FontModel : public QAbstractListModel
{
//    Q_OBJECT
public:
    explicit FontModel(QObject *parent = 0);
    FontModel(const QVector<QLabel*> &labels, QObject *parent = 0);

    int rowCount(const QModelIndex &parent = QModelIndex()) const;

    QVariant data(const QModelIndex &index, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);

    Qt::ItemFlags flags(const QModelIndex &index) const;

    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex());
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex());

    void sort(int column, Qt::SortOrder order = Qt::AscendingOrder);

    QVector<QLabel *> stringList() const;
    void setStringList(const QVector<QLabel *> &vlb_);

    Qt::DropActions supportedDropActions() const;

private:
//    Q_DISABLE_COPY(FontModel)
    QStringList lst;
    QVector<QLabel*> vlb;
};

//#endif // QT_NO_STRINGLISTMODEL

//QT_END_NAMESPACE

//QT_END_HEADER

//#endif // QSTRINGLISTMODEL_H
