#include "directorydatabase.h"

// Qt
#include <QSqlQuery>
#include <QVariant>
#include <QDebug>
#include <QSqlError>
#include <QDir>

#include "utils.h"

#include "initialloadthread.h"

class MainWindow;

DirectoryDatabase::DirectoryDatabase(QObject *parent) :
    connection_name(QString("uithread")),
    QObject(parent)
{
}

DirectoryDatabase::~DirectoryDatabase() {
    delete conn_;
}


void DirecotoryDatabase::setDir(QString dir) {
    this->dir = dir;
    dir_config = dir + "/.booktags";
    path_database = dir_config + "/booktags.sqlite3";
}

void DirectoryDatabase::initDatabase() {

    QSqlDatabase db = getDatabase();

    db.open();

    QSqlQuery query(db);

    QUERY_EXEC(query, "create table if not exists tb_tags ("
                   "tag text primary key"
                   ")"
            );

    QUERY_EXEC(query, "insert into tb_tags (tag) values (\"all\");");

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

    db.close();

}

QSqlDatabase DirectoryDatabase::getDatabase() {
    QSqlDatabase db;

    if (!QSqlDatabase::contains(connectionName))
        db = QSqlDatabase::addDatabase("QSQLITE",connectionName);
    else
        db = QSqlDatabase::database(connectionName);

    db.setDatabaseName(path_database);

    return db;
}

// TODO - carefully think about the design of this multithreading process:
//      Design a new class:
//          DirectoryDatabaseInitializer - using a parallel thread to check directory and load books into the database.
//
//
void DirectoryDatabase::loadAllBooksIntoDatabase() {
    InitialLoadThread* thread_ = new InitialLoadThread(dir, conn_, this);

    connect(thread_, SIGNAL(finished()), thread_, SLOT(deleteLater()));

    connect(thread_, &InitialLoadThread::started,
            this, &DirectoryDatabase::initialDatabaseLoadStarted);

    // forward the signal oneBookAdded
    connect(thread_, &InitialLoadThread::oneItemAdded,
            this, &DirectoryDatabase::initialDatabaseLoadOneBookAdded);

    connect(thread_, &InitialLoadThread::finished,
            this, &DirectoryDatabase::initialDatabaseLoadFinished);

    thread_->start();

}


QStringList DirectoryDatabase::getTags() {
    QSqlDatabase db = getDatabase();
    db.open();

    QSqlQuery query(db);
    QString cmd = QString("select tag from tb_tags;");

    QMutex* mutex = conn_->mutex();

    mutex->lock();
    QUERY_EXEC(query, cmd);
    mutex->unlock();    

    QStringList out;

    while(query.next()) {
        out << query.value(0).toString();
    }

    db.close(); // for close connection

    return out;
}

QStringList DirectoryDatabase::getBooks(const QString& tag) {
    QSqlDatabase db = getDatabase();
    db.open();

    QSqlQuery query(db);
    QString cmd = QString("select filename from tb_matches where tag=\"%1\";").arg(tag.trimmed());


    QMutex* mutex = conn_->mutex();

    mutex->lock();
    QUERY_EXEC(query, cmd);
    mutex->unlock();

    QStringList out;

    while(query.next()) {
        out << query.value(0).toString();
    }

    db.close(); // close connection

    return out;
}

bool DirectoryDatabase::hasTag(const QString& tag) {
    QSqlDatabase db = getDatabase();
    db.open();
    QSqlQuery query(db);
    QString cmd = QString("select exists (select tag from tb_tags where tag=\"%1\");").arg(tag.trimmed());

    QMutex* mutex = conn_->mutex();
    mutex->lock();
    QUERY_EXEC(query, cmd);
    mutex->unlock();

    bool res;
    if (query.next())
        res = query.value(0).toBool();
    else
        qDebug() << "Something wrong.";

    db.close(); // for close connection

    return res;
}

void DirectoryDatabase::addTag(QString tag) {
    QSqlDatabase db = getDatabase();
    db.open();
    QSqlQuery query(db);
    QString cmd = QString("insert into tb_tags (tag) values (\"%1\");").arg(tag.trimmed());

    QMutex* mutex = conn_->mutex();
    mutex->lock();
    QUERY_EXEC(query, cmd);
    mutex->unlock();

    db.close(); // for close connection
}

void DirectoryDatabase::removeTag(QString tag) {
    QSqlDatabase db = getDatabase();
    db.open();
    QSqlQuery query(db);

    QString cmd1 = QString("delete from tb_matches where tag=(\"%1\");").arg(tag);
    QString cmd2 = QString("delete from tb_tags where tag=(\"%1\");").arg(tag);

    QMutex* mutex = conn_->mutex();
    mutex->lock();
    QUERY_EXEC(query, cmd1);
    QUERY_EXEC(query, cmd2);
    mutex->unlock();

    db.close(); // for close connection
}

