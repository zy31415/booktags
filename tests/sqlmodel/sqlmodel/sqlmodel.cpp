#include "sqlmodel.h"

#include <QDebug>

SqlModel::SqlModel(QObject *parent, QSqlDatabase db) :
    QSqlRelationalTableModel(parent, db)
{

}

QVariant SqlModel::data(const QModelIndex &index, int role) const {
    QVariant value = QSqlRelationalTableModel::data(index, role);
    if (value.isValid() && role == Qt::DisplayRole) {
       if (index.column() == 0)
           return value.toString().prepend("#");
       else if (index.column() == 2)
           return value.toString().toUpper();
    }
//    if (role == Qt::TextColorRole && index.column() == 1)
//       return QVariant::fromValue(QColor(Qt::blue));
    qDebug() <<value.toString();
    return value;
}
