/** \file initialloadthread.h
 *
 * This file defines a thread to load books in a directory to database.
 *
 * \author Yang Zhang
 */


#ifndef INITIALLOADTHREAD_H
#define INITIALLOADTHREAD_H

#include <QObject>
#include <QThread>

class InitialLoadThread : public QThread
{
    Q_OBJECT

private:

    ///
    /// \brief Store database connection
    ///
    DatabaseConnection* conn_;

    ///
    /// \brief Store book directory.
    ///
    QString dir;

    ///
    /// \brief Count the number of books that will be processed.
    /// \return Number of books
    ///
    int countNumOfFiles();

public:

    ///
    /// \brief Constructor
    /// \param dir Books dir
    /// \param conn_ Database connection
    /// \param parent
    ///
    InitialLoadThread(
            QString dir,
            DatabaseConnection* conn_,
            QObject* parent=0);

    ///
    /// \brief The function is overloaded to do the actual business.
    ///
    void run() Q_DECL_OVERRIDE;

signals:

    ///
    /// \brief This signal is emitted when the initial load started. The number of books is passed as the parameter.
    /// \param max Number of books
    ///
    void started(int max);

    ///
    /// \brief This signal is emitted when one book is added into the database.
    /// \param current How many books have been possesed.
    /// \param file File name of the added book.
    ///
    void oneItemAdded(int current, QString file);

};

#endif // INITIALLOADTHREAD_H
