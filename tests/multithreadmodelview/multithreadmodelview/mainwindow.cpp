#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "addstringthread.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    tags_ = new TagsList(this);

    QStringList list;
    list<<"aaa"<<"bbb"<<"ccc";

    tags_->setStringList(list);

    ui->listView->setModel(tags_);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_action_New_triggered()
{
    tags_->deleteLater();

    tags_ = new TagsList(this);

    QStringList list;
    list<<"111"<<"222"<<"333";

    tags_->setStringList(list);

    ui->listView->setModel(tags_);

}

void MainWindow::on_action_Add_triggered()
{
    AddStringThread* thread1_ = new AddStringThread(QString("xxx"), tags_, this);

    AddStringThread* thread2_ = new AddStringThread(QString("yyy"), tags_, this);

    thread1_->start();
    thread2_->start();
}
