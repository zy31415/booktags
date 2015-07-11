#include "initialloadthread.h"

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDirIterator>

#include "utils.h"

InitialLoadThread::InitialLoadThread(
        QString dir,
        ConnectionFactory* conn_,
        QObject* parent) :
    QThread(parent),
    dir(dir),
    conn_(conn_)
{}

void InitialLoadThread::run() {
    QSqlDatabase db = conn_->getDatabase(QString("initialloadthread"));
    db.open();

    QMutex* mutex_ = conn_->getMutex();

    QSqlQuery q(db);

    int total = countNumOfFiles();

    int nth = 0;
    QDirIterator it(dir, QDirIterator::Subdirectories);
    while (it.hasNext()) {
        QString f = it.next();
        if (isValidBookFormat(f)){
            QString path = QDir(dir).relativeFilePath(f);
            emit statusBarMessageChanged(path);

            int size =  QFileInfo(f).size();


            QString cm1 = QString("insert into tb_books (filename, size) values (\"%1\", %2);").arg(path).arg(size);
            QString cm2 = QString("insert into tb_matches (tag, filename) values (\"all\", \"%1\");").arg(path);

            mutex_->lock();
            QUERY_EXEC(q, QString(cm1));
            QUERY_EXEC(q, cm2);
            mutex_->unlock();
            nth++;

            emit setProgressBar(total, nth);
            emit oneBookAdded(f);

        }
        emit statusBarMessageChanged("Done!");

    }
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
