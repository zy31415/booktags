#ifndef DATABASE_H
#define  DATABASE_H

#include <QObject>
#include <QMutex>
#include <QSqlDatabase>

class Database : public QObject
{
    Q_OBJECT
public:
    explicit Database(QString path, QString connectionName, QObject *parent = 0);
    ~Database();

    QStringList getTags();
    QStringList getFiles(const QString& tag);

private:
    QString dir, dir_config, path_database, connectionName;

    QSqlDatabase db;
    QMutex mutex;

    void initDatabase();
    void open(); // open a database connection.
    void close(); // close a database connection.

signals:
    void statusBarMessageChanged(QString msg);
    void finished();
    void setProgressBar(int max, int current);
    void bookAdded();


public slots:
    void loadAllBooksIntoDatabase();
    void loadAllBooksIntoDatabase1();

};

#endif // DATABASE_H
