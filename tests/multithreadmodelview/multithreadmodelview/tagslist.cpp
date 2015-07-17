#include "tagslist.h"

#include <QModelIndex>

QMutex TagsList::mutex;

TagsList::TagsList(QObject *parent) :
    QStringListModel(parent)
{

}

void TagsList::appendString(const QString& str) {
    mutex.lock();
    int nrow = rowCount();
    insertRow(nrow);
    QModelIndex idx = index(nrow);
    setData(idx, str);
    mutex.unlock();
}

