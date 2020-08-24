#include "serverprogramming.h"
#include "mainwindow.h"

serverProgramming::serverProgramming(QObject *parent) : QObject(parent)
{

}

void serverProgramming::serverStart() {
    if ( (serverPort<2000) || (serverPort>=65535) ) {
        infoLableText.append("\n The port number is not valid. It must be a number between 2000 and 65535.");
    }
    else {
        if(!myServerClosed) {
            infoLableText.append("\n The server is already running.");
        }
        else {
            myServer = new QTcpServer(this);
            myServer->listen(QHostAddress::Any,serverPort);
            if (myServer->isListening()){
                infoLableText.append("\n The server has started and we are listening for new connections.");
                myServerClosed = false;
                weHaveAClient = false;
            }
            else {
                infoLableText.append("\n Listen() error");
            }
            // Look at the top of mainwindow.cpp to undrestand how these signals and slots works.
            connect(myServer, SIGNAL(newConnection()), this, SLOT(aConnectionArrived()));
            connect(myServer, SIGNAL(newConnection()), this, SIGNAL(newEvent()));
        }
    }
}

void serverProgramming::aConnectionArrived() {
    /*
      It is possible a new client connect us although we have refused it!
      Indeed, athough we rejected it, the OS put it in the queue of clients.
      Therefore, we should check if we already have a client.
      If the answer is YES then we will close the new connection!
    */
    if (weHaveAClient) {
        infoLableText.append("\n A new client tried to connect us! We have closed it because we can not handle more than one.");
        queueClientSocket = myServer->nextPendingConnection();
        infoLableText.append("\n    The closed connection was from IP: ");
        queueClientIp = queueClientSocket->peerAddress().toString();
        infoLableText.append(queueClientIp);
        infoLableText.append(" port: ");
        queueClientPort = QString::number(queueClientSocket->peerPort());
        infoLableText.append(queueClientPort);
        infoLableText.append(" socket descriptor: ");
        queueClientSocketDescriptor = QString::number(queueClientSocket->socketDescriptor());
        infoLableText.append(queueClientSocketDescriptor);
        queueClientSocket->close();
    }
    else {
        clientSocket = myServer->nextPendingConnection();
        weHaveAClient = true;
        infoLableText.append("\n We got a new connectoin from IP: ");
        clientIp = clientSocket->peerAddress().toString();
        infoLableText.append(clientIp);
        infoLableText.append(" port: ");
        clientPort = QString::number(clientSocket->peerPort());
        infoLableText.append(clientPort);
        infoLableText.append(" socket descriptor: ");
        clientSocketDescriptor = QString::number(clientSocket->socketDescriptor());
        infoLableText.append(clientSocketDescriptor);
        // Look at the top of mainwindow.cpp to undrestand how these signals and slots works.
        connect(clientSocket, SIGNAL(disconnected()), this, SLOT(aConnectionLeft()));
        connect(clientSocket, SIGNAL(disconnected()), this, SIGNAL(newEvent()));
    }
}

void serverProgramming::aConnectionLeft() {
    infoLableText.append("\n We lost a connection from IP: ");
    infoLableText.append(clientIp);
    infoLableText.append(" port: ");
    infoLableText.append(clientPort);
    infoLableText.append(" socket descriptor: ");
    infoLableText.append(clientSocketDescriptor);
    clientSocket->close();
    weHaveAClient = false;
}

void serverProgramming::serverStop() {
    if (myServerClosed) {
        infoLableText.append("\n The server is already stopped.");
    }
    else {
        /*
            We must check if there is a client.
            If there is NO client and we try to close it's socket (which is NOT exist) then the program will crash.
            This situation happens when the user press stop button before any client has arrived.
        */
        if (weHaveAClient) {
            clientSocket->close();
            weHaveAClient = false;
            myServer->close();
            infoLableText.append("\n The server has stopped.");
            myServerClosed = true;
        }
        else {
            myServer->close();
            infoLableText.append("\n The server has stopped.");
            myServerClosed = true;
            weHaveAClient = false;
        }
    }
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


