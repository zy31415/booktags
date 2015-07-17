#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "main");

    db.setDatabaseName("test.sqlite3");
    db.open();
    QSqlDatabase db1 = db;





    //model_ = new QSqlTableModel(this, db1);

    model_ = new TableModel(this, db);

    QSqlDatabase db2 = TableModel::getDatabase();
    db2.open();

    qDebug()<<model_->database().databaseName();

    model_->setTable("tb_tags");

    if (!model_->select())
        qDebug() << model_->lastError();

    ui->listView->setModel(model_);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_action_Refresh_triggered()
{
    QSqlDatabase db = TableModel::getDatabase();
    db.open();

    QSqlQuery query(db);

    if (!query.exec("delete from tb_tags where tag=\"aaa\";"))
        qDebug() << query.lastError();

    model_->select();
}
