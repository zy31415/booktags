#include "directoryinitializer.h"

#include <QXmlStreamWriter>
#include <QFile>
#include <QDir>
#include <QDirIterator>

#include <QXmlQuery>
#include <QXmlResultItems>
#include <QXmlNodeModelIndex>
#include <QDebug>
#include <QSqlError>

#include <QSqlQuery>

#include <iostream>

DirectoryInitializer::DirectoryInitializer(QString dir) :
    dir(dir),
    dir_config(dir + "/.booktags/"),
    path_database(dir_config + "/booktags.sqlite3")
{
    if (!QDir(dir_config).exists())
        QDir(dir_config).mkpath(".");

    initDatabase();

    loadAllBooksIntoDatabase();

}

DirectoryInitializer::~DirectoryInitializer()
{

}

void DirectoryInitializer::initDatabase() {

    if (!db.isValid())
        db = (QSqlDatabase::addDatabase("QSQLITE"));
    else
        qDebug() << "You might have initialize database twice.";

    db.setDatabaseName(path_database);
    db.open();

    QSqlQuery query(db);

    query.exec("create table if not exists tb_tags ("
               "name text,"
               "filename text,"
               "primary key (name, filename),"
               "foreign key(filename) references tb_books(filename)"
               ")"
               );

    query.exec("create table if not exists tb_books ("
               "filename text primary key,"
               "title text,"
               "authors text"
               ")"
               );

    db.close(); // for close connection

}

void DirectoryInitializer::loadAllBooksIntoDatabase() {
    db.open();

    QSqlQuery q(db);
    q.prepare("insert into tb_books (filename) values (?)");

    QVariantList names;

    QDirIterator it(dir, QDirIterator::Subdirectories);
    while (it.hasNext()) {
        QString f = it.next();
        if (QFileInfo(f).suffix().toLower() == "pdf" ||
                QFileInfo(f).suffix().toLower() == "mobi" ||
                QFileInfo(f).suffix().toLower() == "epub"
                )
            names << QDir(dir).relativeFilePath(f);
    }


    q.addBindValue(names);

    if (!q.execBatch())
        qDebug() << q.lastError();

    db.close();

}

