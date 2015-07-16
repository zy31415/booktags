#ifndef UPDATETHREAD_H
#define UPDATETHREAD_H

#include <QObject>
#include <QThread>
#include <QMutex>

#include <database.h>

class UpdateThread : public QThread
{
    Q_OBJECT
private:
    Database* db_;

public:
    UpdateThread(Database* db_, QObject* parent=0);

    void run();

signals:
    void addItem(const QString& item);
    void updateList();
};

#endif // UPDATETHREAD_H
