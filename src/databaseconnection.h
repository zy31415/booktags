/** \file databaseconnection.h
 * This header file defines the class DatabaseConnection which is used
 * to handle the database connection to sqlite3 databases.
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
    QString m_file_db;

public:
    ///
    /// \brief Constructor
    /// \param[in] Path to the file of a sqlite3 database.
    ///
    DatabaseConnection(const QString& file_db);

    ///
    /// \brief Return a database object based on connection name.
    /// \param[in] connection name of the database. Default connection name is "uithread".
    /// \return database object.
    ///
    QSqlDatabase database(const QString& connectionName = QString("uithread"));

    ///
    /// \brief Return a lock to database access.
    /// \return QMutex object.
    ///
    QMutex* mutex();
};


///
/// \brief Implementation of the static member: DatabaseConnection::m_mutex
///
QMutex DatabaseConnection::m_mutex;

#endif // DATABASECONNECTION_H
