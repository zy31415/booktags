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

#include "utils.h"

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

// FIXME : How to properly close a database connection? i.e. How to get rid of the following message:
// QSqlDatabasePrivate::addDatabase: duplicate connection name 'qt_sql_default_connection', old connection removed.
DirectoryInitializer::~DirectoryInitializer()
{
    QString connection = db.connectionName();
    db.close();
    db = QSqlDatabase();
    db.removeDatabase(connection);

}

void DirectoryInitializer::initDatabase() {

    if (!db.isValid())
        db = (QSqlDatabase::addDatabase("QSQLITE"));
    else
        qDebug() << "You might have initialize database twice.";

    db.setDatabaseName(path_database);
    db.open();

    QSqlQuery query(db);

    QUERY_EXEC(query, "create table if not exists tb_tags ("
                   "tag text primary key"
                   ")"
            );

    QUERY_EXEC(query, "create table if not exists tb_books ("
                   "filename text primary key,"
                   "title text,"
                   "authors text,"
                   "size integer"
                   ")");

    QUERY_EXEC(query, "create table if not exists tb_matches ("
                   "tag text,"
                   "filename text,"
                   "foreign key (tag) references tb_tags(tag),"
                   "foreign key (filename) references tb_books(filename)"
                   ")");

}


// TODO : use progress bar and multithreading here.
void DirectoryInitializer::loadAllBooksIntoDatabase() {

    QSqlQuery q(db);
    QUERY_EXEC(q, "insert into tb_tags (tag) values (\"all\")");


    QSqlQuery q1(db);
    q1.prepare("insert into tb_books (filename, size) values (?, ?)");

    QSqlQuery q2(db);
    q2.prepare("insert into tb_matches (tag, filename) values (\"all\", ?)");

    QVariantList filenames, filesizes;

    QDirIterator it(dir, QDirIterator::Subdirectories);
    while (it.hasNext()) {
        QString f = it.next();
        if (QFileInfo(f).suffix().toLower() == "pdf" ||
                QFileInfo(f).suffix().toLower() == "mobi" ||
                QFileInfo(f).suffix().toLower() == "epub"
                ) {
            filenames << QDir(dir).relativeFilePath(f);
            filesizes << QFileInfo(f).size();
        }

    }


    q1.addBindValue(filenames);
    q1.addBindValue(filesizes);

    q2.addBindValue(filenames);

    QUERY_EXECBATCH(q1);
    QUERY_EXECBATCH(q2);
}



