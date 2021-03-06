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
                infoLableText.append("\n The server is running and we are listening for new connections.");
                myServerClosed = false;
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
    clientSocket = myServer->nextPendingConnection();
    weHaveAClient = true;
    infoLableText.append("\n We got a new connectoin from IP: ");
    clientIp = clientSocket->peerAddress().toString();
    infoLableText.append(clientIp);
    infoLableText.append(" port: ");
    clientPort = QString::number(clientSocket->peerPort());
    infoLableText.append(clientPort);

    // Look at the top of mainwindow.cpp to undrestand how these signals and slots works.
    connect(clientSocket, SIGNAL(disconnected()), this, SLOT(aConnectionLeft()));
    connect(clientSocket, SIGNAL(disconnected()), this, SIGNAL(newEvent()));
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
    infoLableText.append("\n We lost a connection from: ");
    infoLableText.append(clientIp);
    infoLableText.append(" port: ");
    infoLableText.append(clientPort);
    weHaveAClient = false;
}

void serverProgramming::serverStop() {
    if (myServerClosed) {
        infoLableText.append("\n The server is already closed.");
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
            infoLableText.append("\n The server is stopped.");
            myServerClosed = true;
        }
        else {
            myServer->close();
            infoLableText.append("\n The server is stopped.");
            myServerClosed = true;
        }
    }
}


