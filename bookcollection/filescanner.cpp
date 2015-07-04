#include "filescanner.h"

#include <QDirIterator>
#include <QDebug>

FileScanner::FileScanner(const QDir& dir)
{
    QDirIterator it(dir, QDirIterator::Subdirectories);
//    while (it.hasNext()) {
//        qDebug() << it.next();
//    }


}

