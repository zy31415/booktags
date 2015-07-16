#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    db = QSqlDatabase::addDatabase("QSQLITE","test");
    db.setDatabaseName("/home/zy/workspace/booktags/tests/sqlmodel/booktags.sqlite3");
    db.open();

    model_ = new SqlModel(this, db);

    model_->setTable("tb_tags");
    model_->select();

    //model_->setQuery("select tag from tb_tags;", db);

    ui->listView->setModel(model_);

}

MainWindow::~MainWindow()
{
    delete ui;
}
