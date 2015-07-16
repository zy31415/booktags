#ifndef CONNECTIONFACTORY_H
#define CONNECTIONFACTORY_H

#include <QSqlDatabase>
#include <QMutex>

// TODO - make this singleton!
class DatabaseConnection
{
private:
    QMutex mutex;
    QString file_db;

public:
    DatabaseConnection(QString file_db);

    QSqlDatabase database(QString connectionName = QString("uithread"));

    QMutex* getMutex() { return &mutex;}
};

#endif // CONNECTIONFACTORY_H
