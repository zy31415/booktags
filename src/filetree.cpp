/** @file filetree.cpp
*/
#include "filetree.h"

#include <QFileInfo>
#include <QDebug>

///
/// \brief Return an icon according for the input file format.
/// \param input file path
/// \return A pointer to the icon.
///
QIcon* getIcon(QString file) {
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

///
/// \brief Actually create a file path nodes.
/// \param root
/// \param splitted_path
/// \param from
///
void create_node(QStandardItem* root, QStringList splitted_path, int from) {

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

///
/// \brief Add an QStandardItem to the model.
/// \param root QStandardItem
/// \param path
///
///
void add_path(QStandardItem* root, QString path) {
    qDebug() <<path;
    QStandardItem* parentItem = root;

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
