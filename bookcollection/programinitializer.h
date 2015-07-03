#ifndef PROGRAMINITIALIZER_H
#define PROGRAMINITIALIZER_H

#include <QString>

class ProgramInitializer
{
public:
    ProgramInitializer();

    QString getDatabasePath();
    void initDatabase();
};

#endif // PROGRAMINITIALIZER_H
