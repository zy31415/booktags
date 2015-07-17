#include "currentdirectoryconfigurer.h"

// Qt
#include <QSqlQuery>
#include <QVariant>
#include <QDebug>
#include <QSqlError>
#include <QDir>

#include "utils.h"

#include "initialloadthread.h"

class MainWindow;

CurrentDirectoryConfigurer::CurrentDirectoryConfigurer(
        QString dir,
        QObject *parent) :

    QObject(parent),
    dir(dir),
    dir_config(dir + "/.booktags"),
    path_database(dir_config + "/booktags.sqlite3"),
    conn_(new DatabaseConnection(path_database))
{

    if (!QDir(dir_config).exists()) {
        QDir(dir_config).mkpath(".");
        initDatabase();
        loadAllBooksIntoDatabase();
    }

}

CurrentDirectoryConfigurer::~CurrentDirectoryConfigurer() {
    delete conn_;
}

void CurrentDirectoryConfigurer::initDatabase() {

    QSqlDatabase db = conn_->database();

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

}

// TODO - carefully think about the design of this multithreading process.
//          Avoid using parent() -  this is not a good design.
//
void CurrentDirectoryConfigurer::loadAllBooksIntoDatabase() {
    InitialLoadThread* thread_ = new InitialLoadThread(dir, conn_, this);

    connect(thread_, SIGNAL(finished()), thread_, SLOT(deleteLater()));
    connect(thread_, SIGNAL(initialLoadStarted(int)),
            parent(), SLOT(setStatusBarForInitialLoading(int)));
    connect(thread_, SIGNAL(oneItemAdded(int,QString)),
            parent(), SLOT(updateStatusBarForInitialLoading(int, QString)));

    connect(thread_, SIGNAL(statusBarMessageChanged(QString)),
            parent(), SLOT(changeStatusBarMessage(QString)));

    thread_->start();

}


QStringList CurrentDirectoryConfigurer::getTags() {
    QSqlDatabase db = conn_->database();
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

QStringList CurrentDirectoryConfigurer::getFiles(const QString& tag) {
    QSqlDatabase db = conn_->database();
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

bool CurrentDirectoryConfigurer::hasTag(const QString& tag) {
    QSqlDatabase db = conn_->database();
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

void CurrentDirectoryConfigurer::addTag(QString tag) {
    QSqlDatabase db = conn_->database();
    db.open();
    QSqlQuery query(db);
    QString cmd = QString("insert into tb_tags (tag) values (\"%1\");").arg(tag.trimmed());

    QMutex* mutex = conn_->mutex();
    mutex->lock();
    QUERY_EXEC(query, cmd);
    mutex->unlock();

    db.close(); // for close connection
}

void CurrentDirectoryConfigurer::removeTag(QString tag) {
    QSqlDatabase db = conn_->database();
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
