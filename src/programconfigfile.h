/** @file programconfigfile.h
 *
 * This file defines a class ProgramConfigFile which is used to manage
 * a xml config file for the program.
 *
 * @author Yang Zhang
 *
 */

#ifndef PROGRAMCONFIGFILE_H
#define PROGRAMCONFIGFILE_H

#include <QFile>
#include <QDir>
#include <QDomDocument>
#include <QStringList>

class ProgramConfigFile
{
private:

    ///
    /// \brief Directory for creating program directory.
    ///
    static QString base_dir;

    ///
    /// \brief The program directory.
    ///
    static QString prog_dir;

    ///
    /// \brief The basename of the xml config file
    ///
    static QString configFileBaseName;

    ///
    /// \brief The path to the xml config file
    ///
    static QString configFilePath;

    ///
    /// \brief The file object for the xml config file.
    ///
    QFile configFile;


    static QDomNode getHistoryDirectoresNode(QDomDocument& doc);
    static QDomNode getCurrentDirectoryNode(QDomDocument& doc);
    static QDomNode getBookCollectionNode(QDomDocument& doc);
    static QDomNode searchNodeByTagNameAmongSiblings(QDomNode firstChild, QString tagName);

public:

    ///
    /// \brief Constructor
    ///
    ProgramConfigFile();

    ///
    /// \brief Initialize the config file
    ///
    void initConfigFile();

    void updateHistoryDirectories(QDir dir);

    ///
    /// \brief If the program config exists.
    /// \return true - Yes; false - No.
    ///
    bool ifConfigFileExist();

    ///
    /// \brief Get current directory for books
    /// \return the current directory for books
    ///
    QString getCurrentDirectory();

    ///
    /// \brief Set current directory for books
    /// \param dir
    ///
    void setCurrentDirectory(QString dir);
};


#endif // PROGRAMCONFIGFILE_H
