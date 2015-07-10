#include "currentdirectoryconfigurer.h"

// Qt
#include <QSqlQuery>
#include <QVariant>
#include <QDebug>
#include <QSqlError>

#include "utils.h"


CurrentDirectoryConfigurer::CurrentDirectoryConfigurer(
        QString dir,
        QObject *parent) :
    QObject(parent),
    dir(dir)
{
    initializer_ = new DirectoryInitializer(dir, this);
    connect(initializer_, SIGNAL(finished()),
            initializer_, SLOT(deleteLater()));
    initializer_->start();

    path_database = initializer_->getPathDatabase();

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

    QString cmd1 = QString("delete from tb_matches where tag=(\"%1\");").arg(tag);
    QUERY_EXEC(query, cmd1);

    QString cmd2 = QString("delete from tb_tags where tag=(\"%1\");").arg(tag);
    QUERY_EXEC(query, cmd2);

    db.close(); // for close connection
}
