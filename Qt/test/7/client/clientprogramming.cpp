#include "clientprogramming.h"
#include "mainwindow.h"

clientProgramming::clientProgramming(QObject *parent) : QObject(parent)
{

}

void clientProgramming::myConnect(){
    if ( (serverIp.isNull()) || (serverPort<2000) || (serverPort>=65535) ) {
        if (serverIp.isNull()) {
            infoLableText.append("\n The IP address is not valid.");
        }
        if ((serverPort<2000) || (serverPort>=65535)) {
            infoLableText.append("\n The port number is not valid. It must be a number between 2000 and 65535.");
        }
    }
    else {
        socketState = mySocket.state();
        if(socketState == 3) {
            infoLableText.append("\n We are already connected.");
        }
        else {
            closeButton = false;
            mySocket.connectToHost(serverIp,serverPort);
            mySocket.waitForConnected(serverPort);
            socketState = mySocket.state();
            if(socketState == 3) {
                infoLableText.append("\n We have connected to IP: ");
                infoLableText.append(serverIp.toString());
                infoLableText.append(" port: ");
                serverPortString = QString::number(serverPort);
                infoLableText.append(serverPortString);
                connect(&mySocket, SIGNAL(disconnected()), this, SLOT(serverClosed()));
                connect(&mySocket, SIGNAL(disconnected()), this, SIGNAL(newEvent()));
            }
            else {
                infoLableText.append("\n Because of one of the following reasons we failed to connect.");
                infoLableText.append("\n    1. The IP address and port number are not matched with the server.");
                infoLableText.append("\n    2. The server is not running.");
            }
        }
    }
}

void clientProgramming::myDisconnect(){
    socketState = mySocket.state();
    if(socketState == 0) {
        infoLableText.append("\n We are not connected.");
    }
    else {
        closeButton = true;
        mySocket.disconnectFromHost();
        socketState = mySocket.state();
        if(socketState == 0) {
            infoLableText.append("\n We have disconnected from IP: ");
            infoLableText.append(serverIp.toString());
            infoLableText.append(" port: ");
            infoLableText.append(serverPortString);
        }
        else {
            infoLableText.append("\n We failed to disconnect.");
        }
    }
}

void clientProgramming::serverClosed() {
    socketState = mySocket.state();
    if ((!closeButton) & (socketState==0)) {
        // We must disconnect the signal otherwise, it will perfom the slot multiple times.
        disconnect(&mySocket, SIGNAL(disconnected()), this, SLOT(serverClosed()));
        mySocket.close();
        infoLableText.append("\n The server has closed our connection.");
    }
}
