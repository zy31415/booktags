#include "programconfigfile.h"

#include <QXmlStreamWriter>
#include <QDebug>


ProgramConfigFile::ProgramConfigFile() {
    //QString base_dir = QDir::homePath();
    QString base_dir(".");
    QString prog_dir = base_dir + QString("/.bookcollection/");

    if (!QDir(prog_dir).exists())
        QDir(prog_dir).mkpath(".");

    QString filebasename("config.xml");
    QString filename(prog_dir + filebasename);

    configFile.setFileName(filename);
}

bool ProgramConfigFile::ifConfigFileExist() {
    return configFile.exists();
}

void ProgramConfigFile::initConfigFile() {

    QFileInfo info(configFile);

    QDir path(info.path());
    if (path.exists())
        path.mkpath(".");

    configFile.open(QIODevice::WriteOnly);

    QXmlStreamWriter stream(&configFile);
    stream.setAutoFormatting(true);
    stream.writeStartDocument();

    stream.writeStartElement("bookCollection");

    stream.writeStartElement("currentDirectory");
    stream.writeEndElement(); // bookmark

    stream.writeStartElement("recentDirectories");
    stream.writeEndElement(); // bookmark

    stream.writeEndElement(); // bookmark

    stream.writeEndDocument();

    configFile.close();
}

void ProgramConfigFile::updateHistoryDirectories(QDir dir) {
    QDomDocument doc;

    configFile.open( QIODevice::ReadOnly | QIODevice::Text );
    doc.setContent(&configFile);
    configFile.close();

    QDomNode node = getHistoryDirectoresNode(doc);

    QDomElement newElement = doc.createElement("dir");
    newElement.appendChild(doc.createTextNode(dir.absolutePath()));
    node.appendChild(newElement);

    configFile.open( QIODevice::WriteOnly | QIODevice::Text );
    QTextStream stream( &configFile );
    stream << doc.toString();
    configFile.close();
}

QString ProgramConfigFile::getCurrentDirectory() {
    QDomDocument doc;

    configFile.open( QIODevice::ReadOnly | QIODevice::Text );
    doc.setContent(&configFile);
    configFile.close();

    QDomNode node = getCurrentDirectoryNode(doc);

    return node.toElement().text();
}

QDomNode ProgramConfigFile::getHistoryDirectoresNode(QDomDocument& doc) {
    QDomNode nn = getBookCollectionNode(doc);
    QDomNode n = nn.firstChild();
    return searchNodeByTagNameAmongSiblings(n, QString("historyDirectories"));
}

QDomNode ProgramConfigFile::getCurrentDirectoryNode(QDomDocument& doc) {
    QDomNode nn = getBookCollectionNode(doc);
    QDomNode n = nn.firstChild();
    return searchNodeByTagNameAmongSiblings(n, QString("currentDirectory"));
}

QDomNode ProgramConfigFile::getBookCollectionNode(QDomDocument& doc) {
    QDomNode n = doc.firstChild();
    return searchNodeByTagNameAmongSiblings(n, QString("bookCollection"));
}

QDomNode ProgramConfigFile::searchNodeByTagNameAmongSiblings(QDomNode firstChild, QString tagName) {
    QDomNode n = firstChild;
    while(!n.isNull()) {
        if(n.isElement()) {
            QDomElement e = n.toElement();
            if(e.tagName() == tagName)
                return n;
        }
        n = n.nextSibling();
    }
    return QDomNode();
}

//void ProgramConfigFile::removeSupervisedDirectory(QString dir) {
//    QDomDocument doc;

//    configFile.open( QIODevice::ReadOnly | QIODevice::Text );
//    doc.setContent(&configFile);
//    configFile.close();

//    QDomNode node = getSupervisedDirectoresNode(doc);

//    QDomNode n = node.firstChild();
//    while(!n.isNull()) {
//        if(n.isElement()) {
//            QDomElement e = n.toElement();
//            qDebug() << dir;
//            if(e.text().trimmed() == dir.trimmed()) {
//                node.removeChild(n);
//                break;
//            }
//        }
//        n = n.nextSibling();
//    }

//    configFile.open( QIODevice::WriteOnly | QIODevice::Text );
//    QTextStream stream( &configFile );
//    stream << doc.toString();
//    configFile.close();


//}

QString ProgramConfigFile::getCurrentDirectory() {
    QDomDocument doc;

    configFile.open( QIODevice::ReadOnly | QIODevice::Text );
    doc.setContent(&configFile);
    configFile.close();

    QDomNode n = getCurrentDirectoryNode(doc);
    return n.firstChild().toElement().text();
}
