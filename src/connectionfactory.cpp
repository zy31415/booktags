#include "connectionfactory.h"

ConnectionFactory::ConnectionFactory(QString file_db) : file_db(file_db)
{

}

QSqlDatabase ConnectionFactory::getDatabase(QString connectionName) {
    QSqlDatabase db;

    if (!QSqlDatabase::contains(connectionName))
        db = QSqlDatabase::addDatabase("QSQLITE",connectionName);
    else
        db = QSqlDatabase::database(connectionName);

    db.setDatabaseName(file_db);

    return db;
}
