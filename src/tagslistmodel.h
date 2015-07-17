#ifndef TAGSLISTMODEL_H
#define TAGSLISTMODEL_H

#include <QStringListModel>
#include <QMutex>

///
/// \brief This TagsListModel is a thread-safe data model for TagsListView.
///
class TagsListModel : public QStringListModel
{
    Q_OBJECT

public:
    TagsListModel(QObject* parent);
    void setTagsList(const QStringList& tags);

    ///
    /// \brief Append a tag to the tags list.
    /// \param tag that will be appended.
    ///
    void appendString(const QString& tag);

private:
    ///
    /// \brief mutex lock used to lock the operation on the model.
    /// This is a static member which is shared by all objects.
    ///
    static QMutex mutex;
};

#endif // TAGSLISTMODEL_H
