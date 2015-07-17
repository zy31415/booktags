#include "tablemodel.h"

#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>

TableModel::TableModel(QObject *parent, QSqlDatabase db) :
    QSqlTableModel(parent, db)
{
    initDatabase();
}

void TableModel::initDatabase() {
    QSqlDatabase db = getDatabase();

    db.open();

    QSqlQuery query(db);

    if (!query.exec("create table if not exists tb_tags (tag text);"))
        qDebug() << query.lastError();

    if (!query.exec("insert into tb_tags values (\"aaa\");"))
        qDebug() << query.lastError();

    db.close();

}

QSqlDatabase TableModel::getDatabase(const QString& connectionName) {
    QSqlDatabase db;

    if (QSqlDatabase::contains(connectionName))
        db =  QSqlDatabase::database(connectionName);
    else
        db = QSqlDatabase::addDatabase("QSQLITE", connectionName);

    db.setDatabaseName("test.sqlite3");

    db.open();

    return db;

}
