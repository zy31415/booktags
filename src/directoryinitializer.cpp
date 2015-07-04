#include "directoryinitializer.h"

#include <QXmlStreamWriter>
#include <QFile>
#include <QDir>

#include <QXmlQuery>
#include <QXmlResultItems>
#include <QXmlNodeModelIndex>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>

#include <iostream>

#include "programconfigfile.h"

DirectoryInitializer::DirectoryInitializer(QString dir)
{
    ProgramConfigFile configFile;
    configFile.initConfigFile();

    initDatabase();

}

QString DirectoryInitializer::getDatabasePath() {
    QXmlQuery query;
    QString queryUrl("doc('./.bookcollection/config.xml')/bookcollection/databaseFile/text()");
    QString result;
    query.setQuery(queryUrl);
    query.evaluateTo(&result);
    return result.trimmed();
}

void DirectoryInitializer::initDatabase() {
    QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(getDatabasePath());
    db.open();

    QSqlQuery query(db);

    query.exec("create table if not exists tb_tags ("
               "name text"
               ")"
               );

    db.close(); // for close connection

}

