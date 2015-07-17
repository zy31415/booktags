#include "databaseconnection.h"

QMutex DatabaseConnection::m_mutex;

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

QMutex* DatabaseConnection::mutex() {
    return &m_mutex;
}
