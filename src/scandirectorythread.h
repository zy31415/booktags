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
                        const QStringList& books,
                        QObject* parent=0);

    void run() Q_DECL_OVERRIDE;

private:
    QString dir;
    QStringList books;

};

#endif // SCANDIRECTORYTHREAD_H
