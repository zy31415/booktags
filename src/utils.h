#ifndef UTILS_H
#define UTILS_H

#include <QDebug>
#include <QFileInfo>
#include <QSqlError>

#define QUERY_EXEC(query, command) \
    if(!query.exec(command)) qDebug() << query.lastError()

#define QUERY_EXECBATCH(query) \
    if(!query.execBatch()) qDebug() << query.lastError()


#define isValidBookFormat(path) \
    QFileInfo(path).suffix().toLower() == "pdf" || \
    QFileInfo(f).suffix().toLower() == "mobi" || \
    QFileInfo(f).suffix().toLower() == "epub"

#endif // UTILS_H

