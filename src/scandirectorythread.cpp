#include "scandirectorythread.h"

#include <QDirIterator>

#include "utils.h"

ScanDirectoryThread::ScanDirectoryThread(
        const QString& dir,
        const QStringList& books,
        QObject* parent):
    dir(dir),
    books(books),
    QThread(parent)
{}

// TODO - Use QDir::entryList to get a list of files in the directory.
//          Note that Filters can be used to filter book files.
ScanDirectoryThread::run() Q_DECL_OVERRIDE {
    books.sort();
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

}


