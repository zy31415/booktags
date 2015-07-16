#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    TreeModel* tree = new TreeModel(this);

    ui->treeView->setModel(tree);
    ui->listView->setModel(tree);
}

MainWindow::~MainWindow()
{
    delete ui;
}
