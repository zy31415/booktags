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
    conn_(new ConnectionFactory(path_database))
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

    QSqlDatabase db = conn_->getDatabase();

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
    QSqlDatabase db = conn_->getDatabase();
    db.open();

    QSqlQuery query(db);
    QString cmd = QString("select tag from tb_tags;");

    QMutex* mutex = conn_->getMutex();

    mutex->lock();
    QUERY_EXEC(query, cmd);
    mutex->unlock();

    db.close(); // for close connection

    QStringList out;

    while(query.next()) {
        out << query.value(0).toString();
    }

    return out;
}

QStringList CurrentDirectoryConfigurer::getFiles(const QString& tag) {
    QSqlDatabase db = conn_->getDatabase();
    db.open();

    QSqlQuery query(db);
    QString cmd = QString("select filename from tb_matches where tag=\"%1\";").arg(tag.trimmed());


    QMutex* mutex = conn_->getMutex();

    mutex->lock();
    QUERY_EXEC(query, cmd);
    mutex->unlock();

    // for close connection
    QStringList out;

    while(query.next()) {
        qDebug() << query.value(0).toString();
        QString oi = query.value(0).toString();
        out << oi;
    }
    db.close();
    return out;
}

void CurrentDirectoryConfigurer::addTag(QString tag) {
    QSqlDatabase db = conn_->getDatabase();
    db.open();
    QSqlQuery query(db);
    QString cmd = QString("insert into tb_tags (tag) values (\"%1\");").arg(tag.trimmed());

    QMutex* mutex = conn_->getMutex();
    mutex->lock();
    QUERY_EXEC(query, cmd);
    mutex->unlock();

    db.close(); // for close connection
}

void CurrentDirectoryConfigurer::removeTag(QString tag) {
    QSqlDatabase db = conn_->getDatabase();
    db.open();
    QSqlQuery query(db);

    QString cmd1 = QString("delete from tb_matches where tag=(\"%1\");").arg(tag);
    QString cmd2 = QString("delete from tb_tags where tag=(\"%1\");").arg(tag);

    QMutex* mutex = conn_->getMutex();
    mutex->lock();
    QUERY_EXEC(query, cmd1);
    QUERY_EXEC(query, cmd2);
    mutex->unlock();

    db.close(); // for close connection
}
