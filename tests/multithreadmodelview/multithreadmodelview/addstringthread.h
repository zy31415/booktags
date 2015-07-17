#ifndef ADDSTRINGTHREAD_H
#define ADDSTRINGTHREAD_H

#include <QObject>
#include <QThread>


#include "tagslist.h"

class AddStringThread : public QThread
{
public:
    AddStringThread(QString str, TagsList* tags_, QObject* parent=0);

    void run();

private:
    QString str;
    TagsList* tags_;


};

#endif // ADDSTRINGTHREAD_H
