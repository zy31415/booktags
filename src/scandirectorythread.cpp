#include "scandirectorythread.h"

#include <QDirIterator>

#include "utils.h"

ScanDirectoryThread::ScanDirectoryThread(
        const QString& dir,
        QObject* parent):
    dir(dir),
    QThread(parent) {

    db.setDir(dir);
    db.setConnectionName("scandirectory");
}

void ScanDirectoryThread::run() Q_DECL_OVERRIDE {
    // clear tag new:
    db.removeBooksFromTag("new");

    // start comparison
    QStringList books = db.getAllBooks();
    books.sort();

    QStringList files = getSortedFilesList();

    QStringList::iterator b = books.begin();
    QStringList::iterator f = files.begin();

    emit started( books.length() > files.length() ? books.length():files.length());

    int nth = 0;
    while( b != books.end() && f != files.end()) {
        if (*f == *b) {
            b++;
            f++;
        }

        else if (*f < *b) {
            db.addBook(*f);
            db.tagBook("all", *f);
            db.tagBook("new", *f);
            emit newBookFound(*f);
            f++;
        }
        else {
            db.tagBook("lost", *f);
            emit missingFile(*b);
            b++;
        }

        nth++;
        emit updateScanStatus(nth);
    }

    while(b!=books.end()) {
        db.tagBook("lost", *f);
        emit missingFile(*b);
        b++;

        nth++;
        emit updateScanStatus(nth);
    }

    while(f!=files.end()) {
        db.addBook(*f);
        db.tagBook("all", *f);
        db.tagBook("new", *f);
        emit newBookFound(*f);
        f++;

        nth++;
        emit updateScanStatus(nth);
    }
}

QStringList ScanDirectoryThread::getSortedFilesList() {
    QStringList files;

    QDirIterator it(dir, QDirIterator::Subdirectories);
    while (it.hasNext()) {
        QString f = it.next();
        if (isValidBookFormat(f)){
            QString path = QDir(dir).relativeFilePath(f);

            files << path;
        }
    }

    files.sort();
    return files;
}

