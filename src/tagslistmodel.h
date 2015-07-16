#ifndef TAGSLISTMODEL_H
#define TAGSLISTMODEL_H

#include <QSqlTableModel>

class TagsListModel : public QSqlTableModel
{
public:
    TagsListModel(QObject* parent);
    void setTagsList(const QStringList& tags);
};

#endif // TAGSLISTMODEL_H
