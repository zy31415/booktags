#ifndef INITIALLOADTHREAD_H
#define INITIALLOADTHREAD_H

#include <QObject>
#include <QThread>

#include "databaseconnection.h"

class InitialLoadThread : public QThread
{
    Q_OBJECT

private:
    DatabaseConnection* conn_;
    QString dir;

    int countNumOfFiles();

public:
    InitialLoadThread(
            QString dir,
            DatabaseConnection* conn_,
            QObject* parent=0);

    void run();

signals:
    void initialLoadStarted(int max);
    void oneItemAdded(int current, QString file);
    void statusBarMessageChanged(const QString& file);
    void finished();
};

#endif // INITIALLOADTHREAD_H
