#include "updatethread.h"

#include <QSqlDatabase>
#include <QDirIterator>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>

#include "utils.h"

UpdateThread::UpdateThread(Database* db_, QObject* parent) :
    db_(db_), QThread(parent)
{

}

void UpdateThread::run() {
    QSqlDatabase db = db_->getConnection();
    db.setDatabaseName("test.sqlite3");

    QMutex* mutex = db_->getMutex();

    if (!db.open()) {
        qDebug() << db.lastError();
    }

    QSqlQuery q(db);

    QString dir = QString("/home/zy/Dropbox/Reading/career");


    QDirIterator it(dir, QDirIterator::Subdirectories);
    while (it.hasNext()) {
        QString f = it.next();
        if (QFileInfo(f).suffix().toLower() == "pdf" ||
                QFileInfo(f).suffix().toLower() == "mobi" ||
                QFileInfo(f).suffix().toLower() == "epub"
                ) {
            qDebug() << f;
            mutex_->lock();
            QUERY_EXEC(q, QString("insert into tb_tags (tag) values (\"%1\")").arg(f));
            mutex_->unlock();
            //QThread::sleep(2);
            emit addItem(f);
        }

    }

    db.close();
}
