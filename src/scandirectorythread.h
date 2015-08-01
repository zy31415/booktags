/** @file scandirectorythread.h
 *
 * The file defins class ScanDirectoryThread which is used to scan a directory and
 * compare the files in the directory and those in database.
 *
 */

#ifndef SCANDIRECTORYTHREAD_H
#define SCANDIRECTORYTHREAD_H

#include <QThread>

class ScanDirectoryThread : public QThread
{
    Q_OBJECT

public:
    ScanDirectoryThread(QString dir, QObject* parent=0);

    void run() Q_DECL_OVERRIDE;

private:
    QString dir, dir_config, path_database;

};

#endif // SCANDIRECTORYTHREAD_H
