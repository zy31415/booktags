#include "initialloadthread.h"

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDirIterator>

#include "utils.h"

InitialLoadThread::InitialLoadThread(
        QString dir,
        DatabaseConnection* conn_,
        QObject* parent) :
    QThread(parent),
    dir(dir),
    conn_(conn_)
{}

void InitialLoadThread::run() {
    QSqlDatabase db = conn_->database(QString("initialloadthread"));
    db.open();

    QMutex* mutex_ = conn_->mutex();

    QSqlQuery q(db);

    int total = countNumOfFiles();

    emit initialLoadStarted(total);

    int nth = 0;
    QDirIterator it(dir, QDirIterator::Subdirectories);
    while (it.hasNext()) {
        QString f = it.next();
        if (isValidBookFormat(f)){
            QString path = QDir(dir).relativeFilePath(f);

            int size =  QFileInfo(f).size();


            QString cm1 = QString("insert into tb_books (filename, size) values (\"%1\", %2);").arg(path).arg(size);
            QString cm2 = QString("insert into tb_matches (tag, filename) values (\"all\", \"%1\");").arg(path);

            mutex_->lock();
            QUERY_EXEC(q, QString(cm1));
            QUERY_EXEC(q, cm2);
            mutex_->unlock();
            nth++;

            emit oneItemAdded(nth, path);
        }
    }
    emit statusBarMessageChanged("Done!");
    emit finished();
}

int InitialLoadThread::countNumOfFiles() {
    int total = 0;
    QDirIterator it(dir, QDirIterator::Subdirectories);
    while (it.hasNext()) {
        QString f = it.next();
        if (isValidBookFormat(f))
            total++;
    }
    return total;
}
