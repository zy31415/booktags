#ifndef SQLMODEL_H
#define SQLMODEL_H

#include <QSqlTableModel>
#include <QObject>
#include <QVariant>
#include <QSqlDatabase>

class SqlModel : public QSqlTableModel
{
    Q_OBJECT

public:
    SqlModel(QObject* parent, QSqlDatabase db = QSqlDatabase());

    QVariant data(const QModelIndex &item, int role) const Q_DECL_OVERRIDE;

};

#endif // SQLMODEL_H
