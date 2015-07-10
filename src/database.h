#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>

class Database : public QObject
{
    Q_OBJECT
public:
    explicit Database(QString path, QObject *parent = 0);

signals:

public slots:
};

#endif // DATABASE_H
