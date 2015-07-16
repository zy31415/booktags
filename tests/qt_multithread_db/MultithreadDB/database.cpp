#include "database.h"

#include <QThread>

#include "utils.h"

QSqlDatabase Database::getConnection(QString connectionName) {
    QSqlDatabase db;

    if (!db.contains(connectionName))
        db = QSqlDatabase.addDatabase("QSQLITE",connectionName);
    else
        db = QSqlDatabase.database(connectionName);

    return db;
}
