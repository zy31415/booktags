/**
 */



#ifndef CURRENTDIRECTORYCONFIGURER_H
#define CURRENTDIRECTORYCONFIGURER_H

#include <QString>
#include <QStringList>
#include <QObject>

#include "databaseconnection.h"

class CurrentDirectoryConfigurer : public QObject
{
    Q_OBJECT

private:
    QString dir, dir_config, path_database;

    DatabaseConnection* conn_;

public:
    explicit CurrentDirectoryConfigurer(QString dir, QObject *parent = 0);
    ~CurrentDirectoryConfigurer();

    void initDatabase();
    void loadAllBooksIntoDatabase();

    QStringList getTags();
    QStringList getFiles(const QString& tag);

    void addTag(QString tag);
    void removeTag(QString tag);
};

#endif // CURRENTDIRECTORYCONFIGURER_H
