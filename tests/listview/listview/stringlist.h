#ifndef STRINGLIST_H
#define STRINGLIST_H

#include <QStringListModel>
#include <QStringList>

class StringListModel : public QStringListModel
{
    Q_OBJECT

public:
    StringListModel (QObject* parent=0);
    StringListModel(const QStringList & strings, QObject * parent = 0);

    void append(const QString& string);

    bool setData(const QModelIndex & index,
                 const QVariant & value,
                 int role = Qt::EditRole);


};

#endif // STRINGLIST_H
