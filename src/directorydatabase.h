/** @file directorydatabase.h
 * This file defines the class DirectoryDatabase to provide an interface
 * to the database that is used to store tags and books information.
 *
 * The class defines all the fundamental operations to the directory database.
 *
 * @author Yang Zhang
 */

#ifndef DIRECTORYDATABASE_H
#define DIRECTORYDATABASE_H

#include <QString>
#include <QStringList>
#include <QObject>
#include <QSqlDatabase>
#include <QMutex>

class DirectoryDatabase : public QObject
{
    Q_OBJECT

private:
    QString connectionName;
    QString dir, dir_config, path_database;

    ///
    /// \brief mutex lock to makesure that this class is thread safe.
    ///
    static QMutex mutex;

    ///
    /// \brief Get an object of QSqlDatabase which can be used do database operation.
    /// \return An QSqlDatabase object.
    ///
    /// Note that this function is private, so that no other objects can get the
    /// database connection.
    ///
    QSqlDatabase getDatabase();

public:

    ///
    /// \brief Constructor
    /// \param dir books directory
    /// \param parent
    ///
    explicit DirectoryDatabase(QObject *parent = 0);
    ~DirectoryDatabase();

    ///
    /// \brief Set the path of the database file
    /// \param path_database
    ///
    void setDir(const QString& dir);

    ///
    /// \brief Initialize the database
    ///
    void initDatabase();

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
    QStringList getBooks(const QString& tag);

    ///
    /// \brief Add a tag into the database
    /// \param tag tag to be added
    ///
    void addTag(const QString& tag);

    ///
    /// \brief Remove a tag from the database
    /// \param tag
    ///
    void removeTag(const QString& tag);

    ///
    /// \brief If the tag in the database.
    /// \param tag
    /// \return true - yes, false - no
    ///
    bool hasTag(const QString& tag);

    void addBook(const QString& path);

    ///
    /// \brief set the connection name.
    /// \param Connection name. Default name is "uithread".
    ///
    void setConnectionName(const QString& connectionName = QString("uithread"));


    ///
    /// \brief Get all books stored in database.
    /// \return
    ///
    QStringList getAllBooks();

    ///
    /// \brief Assign a tag to a book;
    /// \param tag
    /// \param book
    ///
    void tagBook(const QString& tag,
                 const QString& book);

    ///
    /// \brief Remove all books under a tag.
    /// \param tag
    ///
    /// This function doesn't delete all books from the database.
    ///
    void removeBooksFromTag(const QString& tag);

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
