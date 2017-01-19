//#pragma once
#include "fontmodel.h"
#include <QAbstractListModel>
//#ifndef QT_NO_STRINGLISTMODEL

//QT_BEGIN_NAMESPACE

FontModel::FontModel(QObject *parent)
    : QAbstractListModel(parent)
{
}


FontModel::FontModel(const QVector<QLabel *> &labels, QObject *parent)
    : QAbstractListModel(parent), vlb(labels)
{

}


int FontModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return vlb.count();
}

QVariant FontModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= lst.size())
        return QVariant();

    if (role == Qt::DisplayRole || role == Qt::EditRole)
    {
        return (QString("LABEL"));
//        QLabel* p = vlb.at(index.row());
//        QLabel o = std::move(*p);
    }

    return QVariant();
}

Qt::ItemFlags FontModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return QAbstractItemModel::flags(index) | Qt::ItemIsDropEnabled;

    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable | Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled;
}


bool FontModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.row() >= 0 && index.row() < lst.size()
        && (role == Qt::EditRole || role == Qt::DisplayRole)) {
//        lst.replace(index.row(), value.toString());
//        vlb.replace(index.row(), value.);
        emit dataChanged(index, index);
        return true;
    }
    return false;
}


bool FontModel::insertRows(int row, int count, const QModelIndex &parent)
{
    if (count < 1 || row < 0 || row > rowCount(parent))
        return false;

    beginInsertRows(QModelIndex(), row, row + count - 1);

    for (int r = 0; r < count; ++r)
        vlb.insert(row, new QLabel("labelINSERTED"));

    endInsertRows();

    return true;
}


bool FontModel::removeRows(int row, int count, const QModelIndex &parent)
{
    if (count <= 0 || row < 0 || (row + count) > rowCount(parent))
        return false;

    beginRemoveRows(QModelIndex(), row, row + count - 1);

    for (int r = 0; r < count; ++r)
        vlb.removeAt(row);

    endRemoveRows();

    return true;
}

static bool ascendingLessThan(const QPair<QString, int> &s1, const QPair<QString, int> &s2)
{
    return s1.first < s2.first;
}

static bool decendingLessThan(const QPair<QString, int> &s1, const QPair<QString, int> &s2)
{
    return s1.first > s2.first;
}


void FontModel::sort(int, Qt::SortOrder order)
{
    emit layoutAboutToBeChanged();

    QList<QPair<QString, int> > list;
    for (int i = 0; i < lst.count(); ++i)
        list.append(QPair<QString, int>(lst.at(i), i));

    if (order == Qt::AscendingOrder)
        qSort(list.begin(), list.end(), ascendingLessThan);
    else
        qSort(list.begin(), list.end(), decendingLessThan);

    lst.clear();
    QVector<int> forwarding(list.count());
    for (int i = 0; i < list.count(); ++i) {
        lst.append(list.at(i).first);
        forwarding[list.at(i).second] = i;
    }

    QModelIndexList oldList = persistentIndexList();
    QModelIndexList newList;
    for (int i = 0; i < oldList.count(); ++i)
        newList.append(index(forwarding.at(oldList.at(i).row()), 0));
    changePersistentIndexList(oldList, newList);

    emit layoutChanged();
}

QVector<QLabel*> FontModel::stringList() const
{
    return vlb;
}


void FontModel::setStringList(const QVector<QLabel*> &vlb_)
{
    emit beginResetModel();
    vlb = vlb_;
    emit endResetModel();
}


Qt::DropActions FontModel::supportedDropActions() const
{
    return QAbstractItemModel::supportedDropActions() | Qt::MoveAction;
}

//QT_END_NAMESPACE

//#endif // QT_NO_STRINGLISTMODEL
