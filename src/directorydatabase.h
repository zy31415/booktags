/** @file directorydatabase.h
 * This file defines the class DirectoryDatabase to provide an interface
 * to the database that is used to store tags and books information.
 *
 * @author Yang Zhang
 */

#ifndef DIRECTORYDATABASE_H
#define DIRECTORYDATABASE_H

#include <QString>
#include <QStringList>
#include <QObject>

#include "databaseconnection.h"

class DirectoryDatabase : public QObject
{
    Q_OBJECT

private:
    QString dir, dir_config, path_database;

    DatabaseConnection* conn_;

public:

    ///
    /// \brief Constructor
    /// \param dir books directory
    /// \param parent
    ///
    explicit DirectoryDatabase(QString dir, QObject *parent = 0);
    ~DirectoryDatabase();

    ///
    /// \brief Initialize the database
    ///
    void initDatabase();

    ///
    /// \brief Load all books under the directory to the database.
    ///
    /// This command creates a new thread to do the job so the main thread (UI thread)
    /// won't be locked.
    ///
    void loadAllBooksIntoDatabase();

    ///
    /// \brief Get all tags list from the database
    /// \return All tags list
    ///
    QStringList getTags();

    ///
    /// \brief Get all files list belonging to a tag from the database
    /// \param tag
    /// \return
    ///
    QStringList getFiles(const QString& tag);

    ///
    /// \brief Add a tag into the database
    /// \param tag tag to be added
    ///
    void addTag(QString tag);

    ///
    /// \brief Remove a tag from the database
    /// \param tag
    ///
    void removeTag(QString tag);

    ///
    /// \brief If the tag in the database.
    /// \param tag
    /// \return true - yes, false - no
    ///
    bool hasTag(const QString& tag);

public slots:

signals:
    ///
    /// \brief This signal will be emitted when the initial load of database is finished.
    ///
    void initialDatabaseLoadFinished();

    ///
    /// \brief This signal will be emitted when the initial load of database is started.
    ///
    void initialDatabaseLoadStarted(int);

    ///
    /// \brief This signal will be emitted when the one book added during the inital load of the database.
    ///
    void initialDatabaseLoadOneBookAdded(int, QString);
};

#endif // DIRECTORYDATABASE_H
