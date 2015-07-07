#ifndef PROGRAMINITIALIZER_H
#define PROGRAMINITIALIZER_H

#include <QString>
#include <QSqlDatabase>

class DirectoryInitializer
{
private:
    QString dir, dir_config, path_database;
    QSqlDatabase db;


    void loadAllBooksIntoDatabase();

public:
    DirectoryInitializer(QString dir);
    ~DirectoryInitializer();

    QString getPathDatabase() {return path_database;}

    void initDatabase();
};

#endif // PROGRAMINITIALIZER_H
