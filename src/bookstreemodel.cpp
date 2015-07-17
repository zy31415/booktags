#include "bookstreemodel.h"

#include <QFileInfo>

QIcon BooksTreeModel::icon_dir = QIcon(":/icons/directory.png");
QIcon BooksTreeModel::icon_pdf = QIcon(":/icons/pdf.png");
QIcon BooksTreeModel::icon_epub = QIcon(":/icons/epub.png");
QIcon BooksTreeModel::icon_mobi = QIcon(":/icons/mobi.png");
QIcon BooksTreeModel::icon_file = QIcon(":/icons/file.png");

BooksTreeModel::BooksTreeModel(QObject* parent) :
    QStandardItemModel(parent)
{

}


void BooksTreeModel::setBooks(const QStringList& path) {
    foreach (QString p, path)
        add_path(p);
}


QIcon* BooksTreeModel::getIcon(QString file) {
    if (QFileInfo(file).suffix() == "")
        return &icon_dir;

    if (QFileInfo(file).suffix().toLower() == "pdf")
        return &icon_pdf;

    if (QFileInfo(file).suffix().toLower() == "mobi")
        return &icon_mobi;

    if (QFileInfo(file).suffix().toLower() == "epub")
        return &icon_epub;

    return &icon_file;
}


void BooksTreeModel::create_node(QStandardItem* root, QStringList splitted_path, int from) {

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


void BooksTreeModel::add_path(QString path) {
    QStandardItem* root = invisibleRootItem();
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

