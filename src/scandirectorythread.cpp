#include "scandirectorythread.h"

#include "databaseconnection.h"

ScanDirectoryThread::ScanDirectoryThread(QString dir, QObject* parent):
    dir(dir),
    dir_config(dir + "/.booktags"),
    path_database(dir_config + "/booktags.sqlite3"),
    QThread(parent)
{

}

ScanDirectoryThread::run() Q_DECL_OVERRIDE{
    // TODO -  Path to the database file should be stored in the DatabaseConnection class.
    QSqlDatabase db = DatabaseConnection(path_database);
    db.open();

    QMutex* mutex_ = DatabaseConnection::mutex();

}


