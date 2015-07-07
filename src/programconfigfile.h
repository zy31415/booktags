#ifndef PROGRAMCONFIGFILE_H
#define PROGRAMCONFIGFILE_H

#include <QFile>
#include <QDir>
#include <QDomDocument>
#include <QStringList>

class ProgramConfigFile
{
private:
    QFile configFile;

    static QDomNode getHistoryDirectoresNode(QDomDocument& doc);
    static QDomNode getCurrentDirectoryNode(QDomDocument& doc);
    static QDomNode getBookCollectionNode(QDomDocument& doc);
    static QDomNode searchNodeByTagNameAmongSiblings(QDomNode firstChild, QString tagName);

public:
    ProgramConfigFile();
    void initConfigFile();
    void updateHistoryDirectories(QDir dir);
    bool ifConfigFileExist();
    void removeSupervisedDirectory(QString dir);
    QString getSupervisedDirectory();

    QString getCurrentDirectory();
    void setCurrentDirectory(QString dir);
};


#endif // PROGRAMCONFIGFILE_H
