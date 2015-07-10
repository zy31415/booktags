#include "database.h"

Database::Database(QString path, QObject *parent) :
    QObject(parent),
    path(path)
{
    initDatabase();
}


void Database::initDatabase() {

    if (!db.isValid())
        db = (QSqlDatabase::addDatabase("QSQLITE"));
    else
        qDebug() << "You might have initialize database twice.";

    db.setDatabaseName(path);
    db.open();

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

    db.close();
}

