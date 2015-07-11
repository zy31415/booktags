#ifndef CONNECTIONFACTORY_H
#define CONNECTIONFACTORY_H

#include <QSqlDatabase>
#include <QMutex>

class ConnectionFactory
{
private:
    QMutex mutex;
    QString file_db;

public:
    ConnectionFactory(QString file_db);

    QSqlDatabase getDatabase(QString connectionName = QString("uithread"));

    QMutex* getMutex() { return &mutex;}
};

#endif // CONNECTIONFACTORY_H
