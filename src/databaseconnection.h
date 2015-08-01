/** \file databaseconnection.h
 *
 * This header file defines the class DatabaseConnection which is used
 * to handle the database connection to sqlite3 databases.
 *
 * The default connection is "unithread", which is used in the main thread.
 * In threads other than the main thread, use a different connection.
 *
 * \author Yang Zhang
 */

#ifndef DATABASECONNECTION_H
#define DATABASECONNECTION_H

#include <QSqlDatabase>
#include <QMutex>

///
/// \brief This class manage sqlite3 database connection.
///
class DatabaseConnection
{
private:
    ///
    /// \brief a staic QMutex object shared by all objects of this class to lock the database.
    ///
    static QMutex m_mutex;

    ///
    /// \brief Path to sqlite3 database file.
    ///
    static QString m_file_db;

    ///
    /// \brief Private Constructor
    /// This class will never be instantiated.
    ///
    DatabaseConnection() {}

public:
    ///
    /// \brief Return a database object based on connection name.
    /// \param[in] connection name of the database. Default connection name is "uithread".
    /// \return database object.
    ///
    static QSqlDatabase database(const QString& connectionName = QString("uithread"));

    ///
    /// \brief Return a lock to database access.
    /// \return QMutex object.
    ///
    static QMutex* mutex();
};




#endif // DATABASECONNECTION_H
