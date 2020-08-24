#include "hellothread.h"

hellothread::hellothread()
{

}

void hellothread::run()
{
    for (int i=0;i<5;i++) {
        qDebug() << thread()->currentThreadId() << i;
        QThread::msleep(500);
    }
}

