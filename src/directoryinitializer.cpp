#include "directoryinitializer.h"

#include <QXmlStreamWriter>
#include <QFile>
#include <QFileInfo>
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
    dir_config(dir + "/.booktags"),
    path_database(dir_config + "/booktags.sqlite3")
{
    if (!QDir(dir_config).exists())
        QDir(dir_config).mkpath(".");

    if (!QFile(path_database).exists()) {
        initDatabase();
        loadAllBooksIntoDatabase();
    }

}

DirectoryInitializer::~DirectoryInitializer()
{

}

// TODO: Redesign database
//      tb_tags
//      tb_books
//      tb_matches
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
               "authors text,"
               "size integer"
               ")"
               );

    db.close(); // for close connection

}

void DirectoryInitializer::loadAllBooksIntoDatabase() {
    db.open();

    QSqlQuery q1(db);
    q1.prepare("insert into tb_books (filename, size) values (?, ?)");

    QSqlQuery q2(db);
    q2.prepare("insert into tb_tags (name, filename) values (?, ?)");

    QVariantList filenames, tagnames, filesizes;

    QDirIterator it(dir, QDirIterator::Subdirectories);
    while (it.hasNext()) {
        QString f = it.next();
        if (QFileInfo(f).suffix().toLower() == "pdf" ||
                QFileInfo(f).suffix().toLower() == "mobi" ||
                QFileInfo(f).suffix().toLower() == "epub"
                ) {
            filenames << QDir(dir).relativeFilePath(f);
            tagnames << "all";
            filesizes << QFileInfo(f).size();
        }

    }


    q1.addBindValue(filenames);
    q1.addBindValue(filesizes);

    q2.addBindValue(tagnames);
    q2.addBindValue(filenames);


    if (!q1.execBatch())
        qDebug() << q1.lastError();

    if (!q2.execBatch())
        qDebug() << q2.lastError();

    db.close();

}

