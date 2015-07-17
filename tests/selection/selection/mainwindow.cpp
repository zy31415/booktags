#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    list_ = new QStringListModel(this);

    QStringList list;

    for(int ii=0; ii<20; ii++){
        list << QString("%0").arg(ii);
    }

    list_->setStringList(list);

    ui->listView->setModel(list_);

    selection = ui->listView->selectionModel();

    connect(selection,
            SIGNAL(selectionChanged(const QItemSelection&, const QItemSelection&)),
            this,
            SLOT(selectionChanged(const QItemSelection&, const QItemSelection&)));

    ui->listView->setCurrentIndex(list_->index(10));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::selectionChanged(const QItemSelection& selected,
                                  const QItemSelection& deselected) {
    QModelIndexList list = selected.indexes();

    QModelIndex idx = list[0];

    //qDebug() << deselected.indexes()[0].data(Qt::DisplayRole).toString();
    qDebug() << idx.data(Qt::DisplayRole).toString();

}
