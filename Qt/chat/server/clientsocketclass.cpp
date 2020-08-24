#include "clientsocketclass.h"

clientSocketClass::clientSocketClass(QObject *parent)
    : QObject(parent)
    , m_serverSocket(new QTcpSocket(this))
{
    connect(m_serverSocket, &QTcpSocket::readyRead, this, &clientSocketClass::receiveDataSlot);
    connect(m_serverSocket, &QTcpSocket::disconnected, this, &clientSocketClass::disconnectedSlot);
}

bool clientSocketClass::setSocketDescriptor(qintptr socketDescriptor)
{
    return m_serverSocket->setSocketDescriptor(socketDescriptor);
}

void clientSocketClass::receiveDataSlot() {
    m_serverSocket->waitForReadyRead(100);
    m_serverSocket->read(readData,99);
    emit iGotData(readData);
}

void clientSocketClass::sendData(char recievedData[99]) {
    m_serverSocket->write(recievedData);
}

void clientSocketClass::disconnectedSlot() {
    emit iAmDisconnected(m_serverSocket);
}
