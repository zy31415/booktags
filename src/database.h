#ifndef DATABASE_H
#define  DATABASE_H

#include <QObject>
#include <QMutex>
#include <QSqlDatabase>

class Database : public QObject
{
    Q_OBJECT
public:
    explicit Database(QString path, QObject *parent = 0);
    ~Database();

private:
    QString dir, dir_config, path_database;

    QSqlDatabase db;
    QMutex mutex;

    void initDatabase();
    void open(); // open a database connection.
    void close(); // close a database connection.

signals:
    void statusBarMessageChanged(QString msg);
    void finished();


public slots:
    void loadAllBooksIntoDatabase();

};

#endif // DATABASE_H
