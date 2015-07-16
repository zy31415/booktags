#ifndef TREEMODEL_H
#define TREEMODEL_H

#include <QStandardItemModel>

class TreeModel : public QStandardItemModel
{
    Q_OBJECT

public:
    TreeModel(QObject* parent=0);

    void addPath(QString path);

private:
    void create_node(QStandardItem* root, QStringList splitted_path, int from);
    QIcon* getIcon(QString file);
};

#endif // TREEMODEL_H
