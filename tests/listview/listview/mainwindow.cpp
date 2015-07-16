#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QStringList>
#include <QStringListModel>
#include <QInputDialog>
#include <QDir>

#include <QDebug>
#include "rightclickedmenu.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QStringList* list = new QStringList();

    (*list) << "abc" << "123" << "def" << "ghi";

    listModel = new StringListModel(*list, NULL);

    ui->listView->setEditTriggers(QListView::DoubleClicked);

    ui->listView->setModel(listModel);
    ui->listView->setSelectionMode(QAbstractItemView::ExtendedSelection);

    connect(ui->listView->selectionModel(),
            SIGNAL(selectionChanged(const QItemSelection&, const QItemSelection&)),
            this, SLOT(handleSelectionChanged(const QItemSelection&, const QItemSelection&)));

    connect(ui->listView->selectionModel(),
            SIGNAL(currentChanged(const QModelIndex&,
                                  const QModelIndex&)),
            this, SLOT(handleCurrentChanged(const QModelIndex&,
                                            const QModelIndex&)));

    connect(ui->listView, SIGNAL(doubleClicked(QModelIndex)),
            this, SLOT(handleDoubleClicked(QModelIndex)));

    ui->listView->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->listView, SIGNAL(customContextMenuRequested(QPoint)),
            this, SLOT(userListMenuRequested(QPoint)));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_action_Add_triggered()
{
    bool ok;
    QString text = QInputDialog::getText(this, tr("get text"),
                                         tr("Input text:"), QLineEdit::Normal,
                                         QDir::home().dirName(), &ok);
    if (ok && !text.isEmpty()) {
        listModel->append(text);
    }


}

void MainWindow::on_action_Selected_triggered()
{
    QStringList list;

    foreach(const QModelIndex &index,
            ui->listView->selectionModel()->selectedIndexes())
        list.append(listModel->data(index, Qt::DisplayRole).toString());

    qDebug() <<list;
}

void MainWindow::handleSelectionChanged(const QItemSelection& selected,
                                        const QItemSelection& deselected) {
    if (!deselected.isEmpty() && ! selected.isEmpty())
        qDebug() << "From " << listModel->data(deselected.indexes().first(),Qt::DisplayRole).toString() \
                    << " to " << selected.at(0).indexes().first();
}

void MainWindow::handleCurrentChanged(const QModelIndex&,
                                      const QModelIndex&) {
    qDebug() << "current changed.";
}

void MainWindow::handleDoubleClicked(const QModelIndex&) {
    qDebug() << "Double clicked()";
}

void MainWindow::userListMenuRequested(const QPoint & pos) {
    qDebug() << "userListMenuRequested";
    QPoint globalPos = ui->listView->mapToGlobal(pos);

    RightClickedMenu myMenu;
    myMenu.addAction("Menu Item 1");

    QAction* selectedItem = myMenu.exec(globalPos);

}
