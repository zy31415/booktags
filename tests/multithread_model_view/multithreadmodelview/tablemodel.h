#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include <QSqlTableModel>

class TableModel : public QSqlTableModel
{
    Q_OBJECT

public:
    TableModel(QObject *parent, QSqlDatabase db);

    static QSqlDatabase getDatabase(const QString& connectionName = "main");

private:
    void initDatabase();

};

#endif // TABELMODEL_H
