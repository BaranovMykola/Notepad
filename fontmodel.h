
#ifndef QSTRINGLISTMODEL_H
#define QSTRINGLISTMODEL_H

#include <QLabel>
#include <QtCore/qstringlist.h>
//#include <QtGui/qabstractitemview.h>

QT_BEGIN_HEADER

QT_BEGIN_NAMESPACE

QT_MODULE(Gui)

#ifndef QT_NO_STRINGLISTMODEL

class Q_GUI_EXPORT QStringListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit QStringListModel(QObject *parent = 0);
    QStringListModel(const QStringList &strings, QObject *parent = 0);

    int rowCount(const QModelIndex &parent = QModelIndex()) const;

    QVariant data(const QModelIndex &index, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);

    Qt::ItemFlags flags(const QModelIndex &index) const;

    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex());
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex());

    void sort(int column, Qt::SortOrder order = Qt::AscendingOrder);

    QStringList stringList() const;
    void setStringList(const QStringList &strings);

    Qt::DropActions supportedDropActions() const;

private:
    Q_DISABLE_COPY(QStringListModel)
    QStringList lst;
    QVector<QLabel> vlb;
};

#endif // QT_NO_STRINGLISTMODEL

QT_END_NAMESPACE

QT_END_HEADER

#endif // QSTRINGLISTMODEL_H
