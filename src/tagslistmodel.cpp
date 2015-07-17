#include "tagslistmodel.h"

TagsListModel::TagsListModel(QObject* parent) : QStringListModel(parent)
{

}

QMutex TagsListModel::mutex;

void TagsListModel::setTagsList(const QStringList& tags) {
    setStringList(tags);
}

void TagsListModel::appendString(const QString& tag) {
    mutex.lock();
    int nrow = rowCount();
    insertRow(nrow);
    QModelIndex idx = index(nrow);
    setData(idx, tag);
    mutex.unlock();
}
