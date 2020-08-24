#include "serverprogramming.h"

serverProgramming::serverProgramming(QObject *parent) : QTcpServer(parent)
{

}

void serverProgramming::serverStart() {
    if(serverPort == 0) {
        infoLableText.append("\n The port number is required to start the server.");
    }
    else {
        if ( (serverPort<2000) || (serverPort>=65535) ) {
            infoLableText.append("\n The port number is not valid. It must be a number between 2000 and 65535.");
        }
        else {
            if(!myServerClosed) {
                infoLableText.append("\n The server is already running.");
            }
            else {
                this->listen(QHostAddress::Any,serverPort);
                if (this->isListening()){
                    infoLableText.append("\n The server has started and we are listening for new connections.");
                    myServerClosed = false;
                }
                else {
                    infoLableText.append("\n Listen() error");
                }
            }
        }
    }
}

void serverProgramming::serverStop() {
    if (myServerClosed) {
        infoLableText.append("\n The server is already stopped.");
    }
    else {
        for (clientSocketClass *worker : m_clients) {
            Q_ASSERT(worker);
            worker->m_serverSocket->close();
        }
        this->close();
        infoLableText.append("\n The server has stopped.");
        myServerClosed = true;
    }
}

void serverProgramming::incomingConnection(qintptr socketDescriptor) {
    clientSocketClass *worker = new clientSocketClass(this);
    if (!worker->setSocketDescriptor(socketDescriptor)) {
        worker->deleteLater();
        return;
    }
    m_clients.append(worker);
    infoLableText.append("\n We got a new connection from IP: ");
    infoLableText.append(worker->m_serverSocket->peerAddress().toString());
    infoLableText.append(" port: ");
    infoLableText.append(QString::number(worker->m_serverSocket->peerPort()));
    // Here newEvent emmits because a new client has arrived (Look at top of mainwindo.cpp).
    emit newEvent();
    connect(worker,&clientSocketClass::iAmDisconnected,this,&serverProgramming::aConnectionLeft);
    connect(worker,&clientSocketClass::iGotData,this,&serverProgramming::echo);
}

void serverProgramming::aConnectionLeft(QTcpSocket *disconnectedClient) {
    infoLableText.append("\n We lost a connection from IP: ");
    infoLableText.append(disconnectedClient->peerAddress().toString());
    infoLableText.append(" port: ");
    infoLableText.append(QString::number(disconnectedClient->peerPort()));
    disconnectedClient->close();
    // Here newEvent emmits because a client has left (Look at top of mainwindo.cpp).
    emit newEvent();
}

void serverProgramming::echo(char recievedData[99]) {
    chatLableText.append(recievedData);
    chatLableText.append("\n");
    for (clientSocketClass *worker : m_clients) {
        Q_ASSERT(worker);
        worker->sendData(recievedData);
    }
    // Here newEvent emmits because a new message from one of the clients (Look at top of mainwindo.cpp).
    emit newEvent();
}
