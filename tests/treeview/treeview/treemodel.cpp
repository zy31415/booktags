#include "treemodel.h"

#include <QFileInfo>
#include <QDirIterator>

TreeModel::TreeModel(QObject* parent) : QStandardItemModel(parent)
{
    QDirIterator it("/home/zy/Dropbox/Reading/", QDirIterator::Subdirectories);

    while(it.hasNext()) {
        addPath(it.next());
    }

}

void TreeModel::addPath(QString path) {
    QStandardItem* parentItem = invisibleRootItem();

    QStringList splitted_path = path.split("/", QString::SkipEmptyParts);


    bool isCreateNode = false;
    int ii = 0;

    while (ii < splitted_path.length()) {
        isCreateNode = true;
        QString str = splitted_path[ii];

        int nrow =0;
        while(nrow < parentItem->rowCount()) {
            QString data = parentItem->child(nrow, 0)->data(Qt::DisplayRole).toString();
            if (data == str) {
                isCreateNode = false;
                break;
            }
            nrow++;
        }

        if(isCreateNode)
            break;

        ii++;
        parentItem = parentItem->child(nrow, 0);
    }

    create_node(parentItem, splitted_path, ii);

}

void TreeModel::create_node(QStandardItem* root, QStringList splitted_path, int from) {

    QStandardItem* parentItem = root;

    for (int ii = from; ii < splitted_path.length(); ii++) {
        QString str = splitted_path[ii];
        QStandardItem* item_ = new QStandardItem(str);
        //QIcon* icon_ = new QIcon(":/icons/directory.png");
        item_->setIcon(*getIcon(str));
        parentItem->appendRow(item_);
        parentItem = item_;
    }
}

QIcon* TreeModel::getIcon(QString file) {
    if (QFileInfo(file).suffix() == "")
        return new QIcon(":/icons/directory.png");

    if (QFileInfo(file).suffix().toLower() == "pdf")
        return new QIcon(":/icons/pdf.png");

    if (QFileInfo(file).suffix().toLower() == "mobi")
        return new QIcon(":/icons/mobi.png");

    if (QFileInfo(file).suffix().toLower() == "epub")
        return new QIcon(":/icons/epub.png");

    return new QIcon(":/icons/file.png");;
}

