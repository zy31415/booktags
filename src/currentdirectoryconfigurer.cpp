#include "currentdirectoryconfigurer.h"

// Qt
#include <QSqlQuery>
#include <QVariant>
#include <QDebug>
#include <QSqlError>
#include <QDir>

#include "utils.h"
#include "database.h"

class MainWindow;

CurrentDirectoryConfigurer::CurrentDirectoryConfigurer(
        QString dir,
        QObject *parent) :

    QObject(parent),
    dir(dir),
    dir_config(dir + "/.booktags"),
    path_database(dir_config + "/booktags.sqlite3")
{

    if (!QDir(dir_config).exists())
        QDir(dir_config).mkpath(".");

    initDatabase();
}

CurrentDirectoryConfigurer::~CurrentDirectoryConfigurer() {
}

void CurrentDirectoryConfigurer::initDatabase() {
    Database* task_ = new Database(dir);

    QThread* thread_ = new QThread;
    task_->moveToThread(thread_);

    connect(thread_, SIGNAL(started()), task_, SLOT(loadAllBooksIntoDatabase()));
    connect(task_, SIGNAL(finished()), thread_, SLOT(quit()));
    connect(thread_, SIGNAL(finished()), task_, SLOT(deleteLater()));
    connect(thread_, SIGNAL(finished()), task_, SLOT(deleteLater()));

    // for message:
    connect(task_, SIGNAL(statusBarMessageChanged(QString)),
            parent(), SLOT(changeStatusBarMessage(QString)));

    thread_->start();

}



QStringList CurrentDirectoryConfigurer::getTags() {
//    db.open();

//    QSqlQuery query(db);

    QStringList out;

//    QUERY_EXEC(query, "select distinct tag from tb_tags;");
//    while (query.next()) {
//        out << query.value(0).toString();
//    }


//    db.close(); // for close connection

    return  out;
}

QStringList CurrentDirectoryConfigurer::getFiles(QString tag) {
//    db.open();

//    QSqlQuery query(db);

//    QStringList out;

//    QUERY_EXEC(query, QString("select filename from tb_matches where tag=\"%1\"").arg(tag));

//    while (query.next()) {
//        out << query.value(0).toString();
//    }


//    db.close(); // for close connection

//    return  out;
}

void CurrentDirectoryConfigurer::addTag(QString tag) {
//    db.open();
//    QSqlQuery query(db);
//    QString cmd = QString("insert into tb_tags (tag) values (\"%1\");").arg(tag);

//    QUERY_EXEC(query, cmd);

//    db.close(); // for close connection
}

void CurrentDirectoryConfigurer::removeTag(QString tag) {
//    db.open();
//    QSqlQuery query(db);

//    QString cmd1 = QString("delete from tb_matches where tag=(\"%1\");").arg(tag);
//    QUERY_EXEC(query, cmd1);

//    QString cmd2 = QString("delete from tb_tags where tag=(\"%1\");").arg(tag);
//    QUERY_EXEC(query, cmd2);

//    db.close(); // for close connection
}
