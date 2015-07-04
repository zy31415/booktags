#ifndef PROGRAMINITIALIZER_H
#define PROGRAMINITIALIZER_H

#include <QString>

class DirectoryInitializer
{
public:
    DirectoryInitializer(QString dir);

    QString getDatabasePath();
    void initDatabase();
};

#endif // PROGRAMINITIALIZER_H
