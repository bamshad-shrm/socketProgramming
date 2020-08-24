#include "bamsocket.h"
#include <QTcpSocket>

QTcpSocket mySocket;

bamSocket::bamSocket()
{

}

void bamSocket::bamConnect() {
    mySocket.connectToHost("127.0.0.1",3000);
}

void bamSocket::bamClose() {
    mySocket.close();
}
