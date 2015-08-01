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

/** TODO - Redesign:
 *   1. Replace the action of Initialization of the directory with a new
 *      menu action : Scan Directory, where these things are done:
 *      (1) Get a list of all books in database;
 *      (2) Get a list of all books in the directory;
 *      (3) Compare these two lists and get two new lists:
 *          A. list of new books
 *          B. list of lost books
 *      (4) Add all new books into the database.
 *
 *  2. Show these three lists:
 *      A. list of all books;
 *      B. list of new books
 *      C. list of lost books
 *  "all", "new" and "lost" are three internal tags.
 *  I don't need a "all" tag actually stored in the tag table.
 *  Since the "new" tag is temporary to each scan, thus I don't need that tag in database either.
 *  "lost" is the tag that I have to put into the database during the initialization of the database.
 *
 */
void InitialLoadThread::run() Q_DECL_OVERRIDE {
    QSqlDatabase db = conn_->database(QString("initialloadthread"));
    db.open();

    QMutex* mutex_ = conn_->mutex();

    QSqlQuery q(db);

    int total = countNumOfFiles();

    emit started(total);

    // create a temporary table:
    QString("create temporary table (file text, )");

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
            QUERY_EXEC(q, cm1);
            QUERY_EXEC(q, cm2);
            mutex_->unlock();
            nth++;

            emit oneItemAdded(nth, path);
        }
    }
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
