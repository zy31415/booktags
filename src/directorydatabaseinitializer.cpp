#include "directorydatabaseinitializer.h"

#include <QDir>

DirectoryDatabaseInitializer::DirectoryDatabaseInitializer(QString dir) :
    dir(dir)
{
    if (!QDir(dir_config).exists()) {
        QDir(dir_config).mkpath(".");
        initDatabase();
        loadAllBooksIntoDatabase();
    }
}

