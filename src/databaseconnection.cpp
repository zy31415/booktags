#include "databaseconnection.h"

QMutex DatabaseConnection::m_mutex;

QString DatabaseConnection::m_file_db = QString("");


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

void DatabaseConnection::setDatabaseFile(const QString& file) {
    m_file_db = file;
}
