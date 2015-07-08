#include "currentdirectoryconfigurer.h"

#include "directoryinitializer.h"

#include <QSqlQuery>
#include <QVariant>

#include <QDebug>
#include <QSqlError>

#include "utils.h"


CurrentDirectoryConfigurer::CurrentDirectoryConfigurer(QString dir) :
    dir(dir)
{
    DirectoryInitializer initializer(dir);

    path_database = initializer.getPathDatabase();

    if (!db.isValid())
        db = (QSqlDatabase::addDatabase("QSQLITE"));
    else
        qDebug() << "You might have initialize database twice.";

    db.setDatabaseName(path_database);
}

QStringList CurrentDirectoryConfigurer::getTags() {
    db.open();

    QSqlQuery query(db);

    QStringList out;

    QUERY_EXEC(query, "select distinct tag from tb_tags;");
    while (query.next()) {
        out << query.value(0).toString();
    }


    db.close(); // for close connection

    return  out;
}

QStringList CurrentDirectoryConfigurer::getFiles(QString tag) {
    db.open();

    QSqlQuery query(db);

    QStringList out;

    QUERY_EXEC(query, QString("select filename from tb_matches where tag=\"%1\"").arg(tag));

    while (query.next()) {
        out << query.value(0).toString();
    }


    db.close(); // for close connection

    return  out;
}

void CurrentDirectoryConfigurer::addTag(QString tag) {
    db.open();
    QSqlQuery query(db);
    QString cmd = QString("insert into tb_tags (tag) values (\"%1\");").arg(tag);

    QUERY_EXEC(query, cmd);

    db.close(); // for close connection
}

void CurrentDirectoryConfigurer::removeTag(QString tag) {
    db.open();
    QSqlQuery query(db);
    QString cmd = QString("delete from tb_tags where name=(\"%1\");").arg(tag);

    if (!query.exec(cmd))
        qDebug() << query.lastError();

    db.close(); // for close connection
}
