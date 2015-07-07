#ifndef CURRENTDIRECTORYCONFIGURER_H
#define CURRENTDIRECTORYCONFIGURER_H

#include <QString>
#include <QStringList>
#include <QSqlDatabase>

class CurrentDirectoryConfigurer
{
private:
    QString dir, path_database;
    QSqlDatabase db;

public:
    CurrentDirectoryConfigurer(QString dir);

    QStringList getTags();
    QStringList getFiles(QString tag);

    void addTag(QString tag);
    void removeTag(QString tag);
};

#endif // CURRENTDIRECTORYCONFIGURER_H
