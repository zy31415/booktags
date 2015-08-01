/** @file scandirectorythread.h
 *
 * The file defines class ScanDirectoryThread which is used to scan a directory and
 * compare the files in the directory with those in the database.
 *
 * Some design consideration:
 * Note that no database operation in this class.
 * This class will emit signals which will trigger database operations.
 *
 */

#ifndef SCANDIRECTORYTHREAD_H
#define SCANDIRECTORYTHREAD_H

#include <QThread>

#include "directorydatabase.h"

class ScanDirectoryThread : public QThread
{
    Q_OBJECT

public:

    ///
    /// \brief Constructor
    /// \param dir Directory that will be scanned and compared.
    /// \param books Books list in the database before the scanning.
    /// \param parent
    ///
    ScanDirectoryThread(const QString& dir,
                        QObject* parent=0);

    void run() Q_DECL_OVERRIDE;

private:
    QString dir;
    DirectoryDatabase db;

    QStringList getSortedFilesList();

signals:
    ///
    /// \brief Emit when a new book found in the directory.
    /// \param The path of the found book.
    ///
    void newBookFound(const QString& path);

    ///
    /// \brief Emit when a book in the database cannot found corresponding file on disk.
    /// \param path
    ///
    void missingFile(const QString& path);

    ///
    /// \brief Scanning started
    /// \param max Number of files that need to be scanned.
    ///
    void started(int max);

    ///
    /// \brief Update scan status
    /// \param nth Right now we are on the nth item.
    ///
    void updateScanStatus(int nth);

};

#endif // SCANDIRECTORYTHREAD_H
