#ifndef CURRENTDIRECTORYCONFIGURER_H
#define CURRENTDIRECTORYCONFIGURER_H

#include <QString>
#include <QStringList>
#include <QObject>

#include "directoryinitializer.h"


class CurrentDirectoryConfigurer : public QObject
{
    Q_OBJECT

private:
    QString dir, dir_config, path_database;

public:
    explicit CurrentDirectoryConfigurer(QString dir, QObject *parent = 0);
    ~CurrentDirectoryConfigurer();

    void initDatabase();

    QStringList getTags();
    QStringList getFiles(QString tag);

    void addTag(QString tag);
    void removeTag(QString tag);
};

#endif // CURRENTDIRECTORYCONFIGURER_H
