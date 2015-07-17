#include "tagslistmodel.h"

TagsListModel::TagsListModel(QObject* parent) : QStringListModel(parent)
{

}

QMutex TagsListModel::mutex;

void TagsListModel::appendTags(const QStringList& tags) {
    setStringList(tags);
}

void TagsListModel::appendTag(const QString& tag) {
    mutex.lock();
    int nrow = rowCount();
    insertRow(nrow);
    QModelIndex idx = index(nrow);
    setData(idx, tag);
    mutex.unlock();
}
