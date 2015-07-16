#include "stringlist.h"

#include <QDebug>

StringListModel::StringListModel(QObject* parent) : QStringListModel(parent)
{}

StringListModel::StringListModel(const QStringList & strings,
                       QObject * parent) :
    QStringListModel(strings, parent)
{

}


void StringListModel::append(const QString &string) {
    insertRows(rowCount(), 1);
    setData(index(rowCount()-1), string);
}

bool StringListModel::setData(const QModelIndex & index,
             const QVariant & value,
             int role) {
    QStringListModel::setData(index, value, role);

    qDebug() << "Set data: " << value;
}
