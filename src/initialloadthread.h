#ifndef INITIALLOADTHREAD_H
#define INITIALLOADTHREAD_H

#include <QObject>
#include <QThread>

#include "connectionfactory.h"

class InitialLoadThread : public QThread
{
    Q_OBJECT

private:
    ConnectionFactory* conn_;
    QString dir;

    int countNumOfFiles();

public:
    InitialLoadThread(
            QString dir,
            ConnectionFactory* conn_,
            QObject* parent=0);

    void run();

signals:
    void oneBookAdded(const QString& file);
    void statusBarMessageChanged(const QString& file);
    void setProgressBar(int, int);
    void finished();
};

#endif // INITIALLOADTHREAD_H
