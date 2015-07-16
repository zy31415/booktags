#include "mainwindow.h"
#include <QApplication>
#include <QSplitter>
#include <QFileSystemModel>
#include <QTreeView>
#include <QListView>
#include <QDebug>
#include <QStandardItemModel>


void create_node(QStandardItem* root, QStringList splitted_path, int from) {

    QString str = splitted_path[from];

    QStandardItem* parentItem = root;

    for (int ii = from; ii < splitted_path.length(); ii++) {
        QStandardItem* item_ = new QStandardItem(splitted_path[ii]);
        QIcon* icon_ = new QIcon(":/directory.png");
        item_->setIcon(*icon_);
        parentItem->appendRow(item_);
        parentItem = item_;
    }
}

void add_path(QStandardItem* root, QString path) {
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

int main(int argc, char *argv[])
{
    QApplication A(argc, argv);

    QSplitter *splitter = new QSplitter;

    QString dir = "/home/zy/Dropbox/Readings/science/";

    QStandardItemModel model;
    QStandardItem *parentItem = model.invisibleRootItem();

    add_path(parentItem, dir);

    add_path(parentItem, "/home/zy/workspace/");

    QTreeView *tree = new QTreeView(splitter);
    tree->setModel(&model);

//    tree->setRootIndex(model->index(dir));

//    QListView *list = new QListView(splitter);
//    list->setModel(model);
//    list->setRootIndex(model->index(dir));

    splitter->setWindowTitle("Two views onto the same file sys.");
    splitter->show();


    return A.exec();
}
