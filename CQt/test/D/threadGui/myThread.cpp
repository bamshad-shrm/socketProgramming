#include "myThread.h"
#include <QtCore>

#include <stdio.h> // For perror().
#include <sys/types.h> // For socket(), bind(), listen() and accept().
#include <sys/socket.h> // For socket(), bind(), listen() and accept().
#include <netinet/in.h> // For struct sockaddr_in and htons().
#include <string.h> // For memset().
#include <stdlib.h> // For exit().
#include <arpa/inet.h> // For inet_ntop().
#include <unistd.h> // For close().

#include <QString>



myThread::myThread(QObject *parent) : QThread (parent)
{

}

void myThread::run() {

    /*for (int i=0;i<10000;i++) {

        //QMutex mutex;
        //mutex.lock();
        if(this->Stop) break;
        //mutex.unlock();

        emit numberChanged(i);

        this->msleep(100);

    }*/

    int serverFd, clientFd, portNumber = 3002, backlogValue = 5, sizeOfSockaddrIn, yes=1; // backlogValue is used in listen().
    struct sockaddr_in serverAddress, clientAddress;
    char ip4[INET_ADDRSTRLEN]; //This variable is used in third and forth arguments of inet_ntop().
    socklen_t clilen;
    QString displayText;

    if ((serverFd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket() perror");
        exit(EXIT_FAILURE);
    }



    if (setsockopt(serverFd,SOL_SOCKET,SO_REUSEADDR,&yes,sizeof(int)) == -1) {
        perror("setsockopt");
        exit(1);
    }

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(portNumber); // Host to network short.
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    memset(serverAddress.sin_zero, '\0', sizeof serverAddress.sin_zero); // Zero this if you want to.

    if (bind(serverFd, (struct sockaddr *)&serverAddress, sizeof serverAddress) == -1) {
        perror("bind() perror");
        exit(EXIT_FAILURE);
    }


    if (listen(serverFd,backlogValue) == -1) {
        perror("listen() perror");
        exit(EXIT_FAILURE);
    }

    displayText.append("server: waiting for connections...\n");
    emit screenDisplay(displayText);
    //printf("server: waiting for connections...\n");

    //sizeOfSockaddrIn = sizeof(struct sockaddr_in); //Get the third argument of accept().


    while(1) {




            if(this->Stop) {
                close(serverFd);
                displayText.append("The server is stopped.\n");
                emit screenDisplay(displayText);
                break;
            }

            clientFd = accept(serverFd, (struct sockaddr *)&clientAddress, &clilen);
            if (clientFd == -1) {

                perror("accept() perror");
                exit(EXIT_FAILURE);
            }


            displayText.append("I got a new connection\n");
            emit screenDisplay(displayText);

            //printf("\n I got a connection from (%s , %d)\n\n",inet_ntop(AF_INET, &(clientAddress.sin_addr), ip4, INET_ADDRSTRLEN) ,ntohs(clientAddress.sin_port));


    }

}
