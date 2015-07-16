#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QString>
// Qt
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>
#include <QDirIterator>
#include <QMutex>

class Database
{
private:
    QMutex mutex;

public:
    Database() {}
    QSqlDatabase getConnection(QString connectionName = QString("uithread"));
    QMutex* getMutex() {return &mutex;}

};

#endif // DATABASE_H
