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

    static QDomNode getSupervisedDirectoresNode(QDomDocument& doc);
    static QDomNode getBookCollectionNode(QDomDocument& doc);
    static QDomNode searchNodeByTagNameAmongSiblings(QDomNode firstChild, QString tagName);

public:
    ProgramConfigFile();
    void initConfigFile();
    void addSupervisedDirectory(QDir dir);
    QStringList getSupervisedDirectories();
    bool ifConfigFileExist();
    void removeSupervisedDirectory(QString dir);
    QString getSupervisedDirectory();
};



#endif // PROGRAMCONFIGFILE_H
