#include "clientprogramming.h"
#include "mainwindow.h"

clientProgramming::clientProgramming(QObject *parent) : QObject(parent)
{

}

void clientProgramming::myConnect() {
    if ( (serverIp.isNull()) || (serverPort<2000) || (serverPort>=65535) || userName.isEmpty() || (userName.length() > 19)) {
        if (serverIp.isNull()) {
            connectionLableText.append("\n The IP address is not valid.");
        }
        if ((serverPort<2000) || (serverPort>=65535)) {
            connectionLableText.append("\n The port number is not valid. It must be a number between 2000 and 65535.");
        }
        if (userName.isEmpty()) {
            connectionLableText.append("\n The user name field must be set.");
        }
        if (userName.length() > 19) {
            connectionLableText.append("\n The user name can not be longer than 19 characters.");
        }
    }
    else {
        socketState = mySocket.state();
        if(socketState == 3) {
            connectionLableText.append("\n We are already connected.");
        }
        else {
            disconnectButton = false;
            mySocket.connectToHost(serverIp,serverPort);
            mySocket.waitForConnected(serverPort);
            socketState = mySocket.state();
            if(socketState == 3) {
                connectionLableText.append("\n We have connected to IP: ");
                connectionLableText.append(serverIp.toString());
                connectionLableText.append(" port: ");
                serverPortString = QString::number(serverPort);
                connectionLableText.append(serverPortString);
                // Look at the top of mainwindow.cpp to undrestand how these signals and slots works.
                connect(&mySocket, SIGNAL(disconnected()), this, SLOT(serverClosed()));
                connect(&mySocket, SIGNAL(disconnected()), this, SIGNAL(newEvent()));
                connect(&mySocket, SIGNAL(readyRead()), this, SLOT(recieveMsg()));
                connect(&mySocket, SIGNAL(readyRead()), this, SIGNAL(newEvent()));
            }
            else {
                connectionLableText.append("\n Because of one of the following reasons we failed to connect.");
                connectionLableText.append("\n    1. The IP address and port number are not matched with the server.");
                connectionLableText.append("\n    2. The server is not running.");
            }
        }
    }
}

void clientProgramming::myDisconnect() {
    socketState = mySocket.state();
    if(socketState == 0) {
        connectionLableText.append("\n We are already disconnected.");
    }
    else {
        disconnectButton = true;
        mySocket.disconnectFromHost();
        socketState = mySocket.state();
        if(socketState == 0) {
            connectionLableText.append("\n We have disconnected from IP: ");
            connectionLableText.append(serverIp.toString());
            connectionLableText.append(" port: ");
            connectionLableText.append(serverPortString);
        }
        else {
            connectionLableText.append("\n We failed to disconnect.");
        }
    }
}

void clientProgramming::serverClosed() {
    socketState = mySocket.state();
    if ((!disconnectButton) & (socketState==0)) {
        // We must disconnect the signal otherwise, it will perfom the slot multiple times.
        disconnect(&mySocket, SIGNAL(disconnected()), this, SLOT(serverClosed()));
        mySocket.close();
        connectionLableText.append("\n The server has closed our connection.");
    }
}

void clientProgramming::recieveMsg() {
    mySocket.waitForReadyRead(100);
    mySocket.read(readData,99);
    chatLableText.append("\n");
    chatLableText.append(readData);
    memset(readData, 0, sizeof(readData));
    // We must disconnect the signal otherwise, it will perfom the slot multiple times.
    disconnect(&mySocket, SIGNAL(readyRead()), this, SLOT(recieveMsg()));
    connect(&mySocket, SIGNAL(readyRead()), this, SLOT(recieveMsg()));
    connect(&mySocket, SIGNAL(readyRead()), this, SIGNAL(newEvent()));
}

void clientProgramming::sendMsg() {
    socketState = mySocket.state();
    if (socketState == 3) {
        if (userMsg.isEmpty() || userMsg.length() > 80) {
            if (userMsg.isEmpty()) {
                chatLableText.append("\n Empty message is NOT allowed.");
            }
            if (userMsg.length() > 80) {
                chatLableText.append("\n The message should NOT be longer that 80 characters.");
            }
        }
        else {
            sendMessage = userName + ": " + userMsg;
            for (int var = 0; var < sendMessage.length(); ++var) {
                wirteData[var] = sendMessage[var].toLatin1();
            }
            wirteData[sendMessage.length()] = '\0';
            mySocket.write(wirteData,99);
            // Look at the top of mainwindow.cpp to undrestand how these signals and slots works.
            connect(&mySocket, SIGNAL(readyRead()), this, SLOT(recieveMsg()));
            connect(&mySocket, SIGNAL(readyRead()), this, SIGNAL(newEvent()));
        }
    }
    else {
        chatLableText.append("\n We are NOT connected. Pleas first connect and try again.");
    }
}


