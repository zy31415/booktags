#ifndef UTILS_H
#define UTILS_H

#define QUERY_EXEC(query, command) \
    if(!query.exec(command)) qDebug() << query.lastError()

#define QUERY_EXECBATCH(query) \
    if(!query.execBatch()) qDebug() << query.lastError()


#endif // UTILS_H

