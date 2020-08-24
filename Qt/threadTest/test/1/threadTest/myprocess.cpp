#include "myprocess.h"

myProcess::myProcess()
{

}

void myProcess::processRun() {
    for (int var = 0; var < 100; ++var) {
        qDebug() << var;
        firstProcessLableText = QString::number(var);
        QThread::msleep(100);
    }
}
