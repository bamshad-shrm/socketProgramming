#include "myprocess.h"

myProcess::myProcess()
{

}

void myProcess::run() {
    for (int i = 0;i < 10; i++) {
        number = i;
        qDebug("a");
        emit numberChanged(i);
        QThread::msleep(100);
    }
}
