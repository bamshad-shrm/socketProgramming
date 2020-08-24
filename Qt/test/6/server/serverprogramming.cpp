#include "serverprogramming.h"
#include "ui_serverprogramming.h"

serverProgramming::serverProgramming(QObject *parent) : QObject(parent)
{

}

void serverProgramming::serverStart() {
    myServer = new QTcpServer(this);
    myServer->listen(QHostAddress::Any,3000);
    if (myServer->isListening()){
        infoLableText.append("The server is running and we are listening for new connections.\n");
    }
    else {
        infoLableText.append("\n Listen() error");
    }
    connect(myServer, SIGNAL(newConnection()), this, SLOT(aConnectionArrived()));

}

void serverProgramming::aConnectionArrived() {
    clientSocket = myServer->nextPendingConnection();
    infoLableText.append("\n I got a new connectoin from IP: ");
    clientIp = clientSocket->peerAddress().toString();
    infoLableText.append(clientIp);
    infoLableText.append(" port: ");
    clientPort = QString::number(clientSocket->peerPort());
    infoLableText.append(clientPort);
    connect(clientSocket, SIGNAL(disconnected()), this, SLOT(aConnectionLeft()));
}

void serverProgramming::connectionState() {
    int socketState = clientSocket->state();
    if (socketState == 0) {
        infoLableText.append("\n Connection state: The socket is not connected.");
    }
    if (socketState == 1) {
        infoLableText.append("\n Connection state: The socket is performing a host name lookup.");
    }
    if (socketState == 2) {
        infoLableText.append("\n Connection state: The socket has started establishing a connection.");
    }
    if (socketState == 3) {
        infoLableText.append("\n Connection state: A connection is established.");
    }
    if (socketState == 4) {
        infoLableText.append("\n Connection state: The socket is bound to an address and port.");
    }
    if (socketState == 6) {
        infoLableText.append("\n Connection state: The socket is about to close (data may still be waiting to be written).");
    }
}

void serverProgramming::aConnectionLeft() {
    infoLableText.append("\n I lost a connection from: ");
    infoLableText.append(clientIp);
    infoLableText.append(" port: ");
    infoLableText.append(clientPort);
}

void serverProgramming::serverStop() {
    myServer->close();
    infoLableText.append("\n The server is stopped.");
}
