#ifndef TAGSLIST_H
#define TAGSLIST_H

#include <QStringListModel>
#include <QMutex>


class TagsList : public QStringListModel
{
private:
    static QMutex mutex;

public:
    TagsList(QObject* parent);
    void appendString(const QString& str);
};

#endif // TAGSLIST_H
