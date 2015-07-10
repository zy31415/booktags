#ifndef CURRENTDIRECTORYCONFIGURER_H
#define CURRENTDIRECTORYCONFIGURER_H

#include <QString>
#include <QStringList>
#include <QSqlDatabase>
#include <QObject>

#include "directoryinitializer.h"

class CurrentDirectoryConfigurer : public QObject
{
    Q_OBJECT

private:
    QString dir, path_database;
    QSqlDatabase db;

    DirectoryInitializer* initializer_;

public:
    explicit CurrentDirectoryConfigurer(QString dir, QObject *parent = 0);

    QStringList getTags();
    QStringList getFiles(QString tag);

    void addTag(QString tag);
    void removeTag(QString tag);
};

#endif // CURRENTDIRECTORYCONFIGURER_H
