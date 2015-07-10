#include "database.h"

// Qt
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>
#include <QDirIterator>

// This project
#include "utils.h"

Database::Database(QString dir, QObject *parent) :
    QObject(parent),
    dir(dir),
    dir_config(dir + "/.booktags"),
    path_database(dir_config + "/booktags.sqlite3")
{
    open();
    initDatabase();
}

Database::~Database() {
    close();
}

void Database::open() {
    db = QSqlDatabase::addDatabase("QSQLITE", path_database);
    db.setDatabaseName(path_database);
    db.open();
}

void Database::close() {
    db.close();
    db.removeDatabase(path_database);
}

void Database::initDatabase() {

    QSqlQuery query(db);

    mutex.lock();

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

    mutex.unlock();


}

// TODO : use progress bar and multithreading here.
void Database::loadAllBooksIntoDatabase() {

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

    emit statusBarMessageChanged("Adding books data ...");
    mutex.lock();
    QUERY_EXECBATCH(q1);
    mutex.unlock();

    emit statusBarMessageChanged("Adding matching data ...");
    mutex.lock();
    QUERY_EXECBATCH(q2);
    mutex.unlock();

    //close();

    emit statusBarMessageChanged("Database initialization done!");
    emit finished();

}

