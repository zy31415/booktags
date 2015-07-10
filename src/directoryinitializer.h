#ifndef PROGRAMINITIALIZER_H
#define PROGRAMINITIALIZER_H

#include <QString>
#include <QSqlDatabase>
#include <QThread>

class DirectoryInitializer : public QThread
{
    Q_OBJECT

private:
    QString dir, dir_config, path_database;
    QSqlDatabase db;


    void loadAllBooksIntoDatabase();

public:
    explicit DirectoryInitializer(QString dir, QObject *parent = 0);
    ~DirectoryInitializer();

    QString getPathDatabase() {return path_database;}

    void initDatabase();

    void run();
};

#endif // PROGRAMINITIALIZER_H
