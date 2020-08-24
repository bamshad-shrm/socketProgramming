#include "socketprogramming.h"
#include <QTcpSocket>

socketProgramming::socketProgramming(QObject *parent) : QObject(parent)
{

}

void socketProgramming::mySocket() {

}

void socketProgramming::myConnect() {
    QTcpSocket mySocket;
    mySocket.connectToHost("127.0.0.1",3000);
}
