#include "tagslistmodel.h"

TagsListModel::TagsListModel(QObject* parent) : QStringListModel(parent)
{

}

void TagsListModel::setTagsList(const QStringList& tags) {
    setStringList(tags);
}
