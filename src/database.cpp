#include "database.h"

// Qt
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>
#include <QDirIterator>

// This project
#include "utils.h"

Database::Database(
        QString dir,
        QString connectionName,
        QObject *parent) :
    QObject(parent),
    dir(dir),
    dir_config(dir + "/.booktags"),
    path_database(dir_config + "/booktags.sqlite3"),
    connectionName(connectionName)
{
    open();
    initDatabase();
}

Database::~Database() {
    close();
}

void Database::open() {
    db = QSqlDatabase::addDatabase("QSQLITE", connectionName);
    db.setDatabaseName(path_database);
    db.open();
}

void Database::close() {
    db.close();
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

void Database::loadAllBooksIntoDatabase1() {

    QSqlQuery q(db);
    QUERY_EXEC(q, "insert into tb_tags (tag) values (\"all\")");

    int total = 0;
    QDirIterator it1(dir, QDirIterator::Subdirectories);
    while (it1.hasNext()) {
        QString f = it1.next();
        if (QFileInfo(f).suffix().toLower() == "pdf" ||
                QFileInfo(f).suffix().toLower() == "mobi" ||
                QFileInfo(f).suffix().toLower() == "epub"
                )
            total++;
    }

    int nth = 0;
    QDirIterator it(dir, QDirIterator::Subdirectories);
    while (it.hasNext()) {
        QString f = it.next();
        if (QFileInfo(f).suffix().toLower() == "pdf" ||
                QFileInfo(f).suffix().toLower() == "mobi" ||
                QFileInfo(f).suffix().toLower() == "epub"
                ) {

            QString path = QDir(dir).relativeFilePath(f);
            emit statusBarMessageChanged(path);

            int size =  QFileInfo(f).size();


            QString cm1 = QString("insert into tb_books (filename, size) values (\"%1\", %2);").arg(path).arg(size);
            QString cm2 = QString("insert into tb_matches (tag, filename) values (\"all\", \"%1\");").arg(path);

            mutex.lock();
            QUERY_EXEC(q, QString(cm1));
            QUERY_EXEC(q, cm2);
            mutex.unlock();
            nth++;

            emit setProgressBar(total, nth);
            emit bookAdded();

        }
        emit statusBarMessageChanged("Done!");

    }
    emit finished();

}

QStringList Database::getTags() {
    QSqlQuery query(db);

    QStringList out;

    QUERY_EXEC(query, "select distinct tag from tb_tags;");
    while (query.next()) {
        out << query.value(0).toString();
    }


    db.close(); // for close connection

    return  out;
}

QStringList Database::getFiles(const QString& tag) {
    QSqlQuery query(db);

    QStringList out;

    QUERY_EXEC(query, QString("select filename from tb_matches where tag=\"%1\"").arg(tag));

    while (query.next()) {
        out << query.value(0).toString();
    }


    db.close(); // for close connection

    return  out;
}
