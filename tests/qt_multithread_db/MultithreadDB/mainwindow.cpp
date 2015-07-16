#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QThread>


#include "database.h"
#include "utils.h"
#include "updatethread.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QSqlDatabase db = QSqlDatabase::addDatabase(
                "QSQLITE", "uithread");
    db.setDatabaseName("test.sqlite3");

    db.open();

    QSqlQuery query(db);

    QUERY_EXEC(query, "create table if not exists tb_tags ("
                   "tag text"
                   ")"
            );

    db.close();


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateList() {
    QSqlDatabase db = QSqlDatabase::database("uithread");
    db.setDatabaseName("test.sqlite3");

    if (!db.open()) {
        qDebug() << db.lastError();
    }

    QSqlQuery q(db);

    mutex.lock();
    QUERY_EXEC(q, "select tag from tb_tags;");
    mutex.unlock();

    QStringList files;

    while(q.next()) {
        files << q.value(0).toString();
    }

    db.close();

    ui->listWidget->clear();

    ui->listWidget->addItems(files);
}

void MainWindow::addItem(const QString& item) {
    ui->listWidget->addItem(item);
}

void MainWindow::on_action_Scan_directory_triggered()
{
    UpdateThread* thread_ = new UpdateThread(&db, this);
    connect(thread_, SIGNAL(finished()), thread_, SLOT(deleteLater()));
    connect(thread_, SIGNAL(addItem(const QString&)), this, SLOT(addItem(const QString&)));
    thread_->start();
}

