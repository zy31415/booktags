#include "programinitializer.h"

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

ProgramInitializer::ProgramInitializer()
{
    //QString base_dir = QDir::homePath();
    QString base_dir(".");
    QString prog_dir = base_dir + QString("/.bookcollection/");

    if (!QDir(prog_dir).exists())
        QDir(prog_dir).mkpath(".");

    QString filebasename("config.xml");

    QString filename = prog_dir + filebasename;

    QFile file(filename);

    file.open(QIODevice::WriteOnly);

    QXmlStreamWriter stream(&file);
    stream.setAutoFormatting(true);
    stream.writeStartDocument();
    stream.writeStartElement("bookcollection");
    stream.writeTextElement("configDir", QDir(prog_dir).absolutePath());
    stream.writeTextElement("databaseFile", QDir(prog_dir + "database.sqlite3").absolutePath());
    stream.writeEndElement(); // bookmark
    stream.writeEndDocument();

    file.close();

    initDatabase();

}

QString ProgramInitializer::getDatabasePath() {
    QXmlQuery query;
    QString queryUrl("doc('./.bookcollection/config.xml')/bookcollection/databaseFile/text()");
    QString result;
    query.setQuery(queryUrl);
    query.evaluateTo(&result);
    return result.trimmed();
}

void ProgramInitializer::initDatabase() {
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

