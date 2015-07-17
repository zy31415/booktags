#include "addstringthread.h"
#include <QDebug>

AddStringThread::AddStringThread(QString str, TagsList* tags_, QObject* parent) :
    QThread(parent),
    str(str),
    tags_(tags_)
{

}

void AddStringThread::run() {
    for(int ii = 0; ii < 100; ii++) {

        tags_->appendString(str);
        int time = qrand();
        qDebug() << time;
        msleep(time/1000000);
    }
}

