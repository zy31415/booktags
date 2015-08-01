#include "directorydatabaseinitializer.h"

#include <QDir>

#include "databaseconnection.h"

DirectoryDatabaseInitializer::DirectoryDatabaseInitializer(QString dir) :
    dir(dir),
    dir_config(dir + "/.booktags"),
    path_database(dir_config + "/booktags.sqlite3"),
{
    if (!QDir(dir_config).exists()) {
        QDir(dir_config).mkpath(".");
        DatabaseConnection::setDatabaseFile(path_database);
    }
}

