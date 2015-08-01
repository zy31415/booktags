#include "directorydatabase.h"

// Qt
#include <QSqlQuery>
#include <QVariant>
#include <QDebug>
#include <QSqlError>
#include <QDir>

#include "utils.h"


QMutex DirectoryDatabase::mutex;

DirectoryDatabase::DirectoryDatabase(QObject *parent) :
    connectionName(QString("uithread")),
    QObject(parent)
{
}

DirectoryDatabase::~DirectoryDatabase() {
}


void DirectoryDatabase::setDir(const QString& dir) {
    this->dir = dir;
    dir_config = dir + "/.booktags";
    path_database = dir_config + "/booktags.sqlite3";
}

void DirectoryDatabase::setConnectionName(const QString& connectionName) {
    this->connectionName = connectionName;
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

void DirectoryDatabase::initDatabase() {
    if (!QDir(dir_config).exists())
        QDir().mkdir(dir_config);

    QSqlDatabase db = getDatabase();

    db.open();

    QSqlQuery query(db);

    mutex.lock();

    // create table for tags;
    QUERY_EXEC(query, "create table if not exists tb_tags ("
                   "tag text primary key"
                   ")"
            );

    // Add these three initial tags if they don't exist.
    QStringList list;
    list << "all" << "new" << "lost";
    foreach (QString l, list)
        QUERY_EXEC(query,QString(
                       "insert into tb_tags (tag) "
                       "select tag from tb_tags "
                       "where not exists"
                       "(select * from tb_tags where tag=\"%1\");").arg(l));

    // create table for books
    QUERY_EXEC(query, "create table if not exists tb_books ("
                   "filename text primary key,"
                   "title text,"
                   "authors text,"
                   "size integer"
                   ")");

    // create table for tag-book matches.
    QUERY_EXEC(query, "create table if not exists tb_matches ("
                   "tag text,"
                   "filename text,"
                   "foreign key (tag) references tb_tags(tag),"
                   "foreign key (filename) references tb_books(filename)"
                   ")");

    mutex.unlock();

    db.close();

}

QStringList DirectoryDatabase::getTags() {
    QSqlDatabase db = getDatabase();
    db.open();

    QSqlQuery query(db);
    QString cmd = QString("select tag from tb_tags;");

    mutex.lock();
    QUERY_EXEC(query, cmd);
    mutex.unlock();

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

    mutex.lock();
    QUERY_EXEC(query, cmd);
    mutex.unlock();

    QStringList out;

    while(query.next()) {
        out << query.value(0).toString();
    }

    db.close(); // close connection

    return out;
}

QStringList DirectoryDatabase::getAllBooks() {
    QSqlDatabase db = getDatabase();
    db.open();

    QSqlQuery query(db);
    QString cmd = QString("select filename from tb_books;");

    mutex.lock();
    QUERY_EXEC(query, cmd);
    mutex.unlock();

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

    mutex.lock();
    QUERY_EXEC(query, cmd);
    mutex.unlock();

    bool res;
    if (query.next())
        res = query.value(0).toBool();
    else
        qDebug() << "Something wrong.";

    db.close(); // for close connection

    return res;
}

void DirectoryDatabase::addTag(const QString& tag) {
    QSqlDatabase db = getDatabase();
    db.open();
    QSqlQuery query(db);
    QString cmd = QString("insert into tb_tags (tag) values (\"%1\");").arg(tag.trimmed());

    mutex.lock();
    QUERY_EXEC(query, cmd);
    mutex.unlock();

    db.close(); // for close connection
}

void DirectoryDatabase::removeTag(const QString& tag) {
    QSqlDatabase db = getDatabase();
    db.open();
    QSqlQuery query(db);

    QString cmd1 = QString("delete from tb_matches where tag=(\"%1\");").arg(tag);
    QString cmd2 = QString("delete from tb_tags where tag=(\"%1\");").arg(tag);

    mutex.lock();
    QUERY_EXEC(query, cmd1);
    QUERY_EXEC(query, cmd2);
    mutex.unlock();

    db.close(); // for close connection
}

void DirectoryDatabase::addBook(const QString& path) {
    QSqlDatabase db = getDatabase();
    db.open();
    QSqlQuery query(db);
    QString cmd = QString("insert into tb_books (filename) values (\"%1\");").arg(path.trimmed());

    mutex.lock();
    QUERY_EXEC(query, cmd);
    mutex.unlock();

    db.close(); // for close connection
}

void DirectoryDatabase::tagBook(const QString& tag,
                                const QString& path) {
    QSqlDatabase db = getDatabase();
    db.open();
    QSqlQuery query(db);
    QString cmd = QString("insert into tb_matches (tag, filename) values (\"%1\",\"%2\");")
            .arg(tag.trimmed()).arg(path.trimmed());

    mutex.lock();
    QUERY_EXEC(query, cmd);
    mutex.unlock();

    db.close(); // for close connection
}

void DirectoryDatabase::removeBooksFromTag(const QString& tag) {
    QSqlDatabase db = getDatabase();
    db.open();
    QSqlQuery query(db);

    QString cmd = QString("delete from tb_matches where tag=\"%1\";")
            .arg(tag.trimmed());

    mutex.lock();
    QUERY_EXEC(query, cmd);
    mutex.unlock();

    db.close(); // for close connection
}
