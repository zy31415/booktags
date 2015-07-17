#include "databaseconnection.h"

DatabaseConnection::DatabaseConnection(const QString& file_db) : m_file_db(file_db)
{
}


QSqlDatabase DatabaseConnection::database(const QString& connectionName) {
    QSqlDatabase db;

    if (!QSqlDatabase::contains(connectionName))
        db = QSqlDatabase::addDatabase("QSQLITE",connectionName);
    else
        db = QSqlDatabase::database(connectionName);

    db.setDatabaseName(m_file_db);

    return db;
}

QMutex* QSqlDatabase::mutex() {
    return &m_mutex;
}
