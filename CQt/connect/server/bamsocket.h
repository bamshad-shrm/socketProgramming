#ifndef BAMSOCKET_H
#define BAMSOCKET_H

#include <iostream>
#include <sys/types.h> // For socket(), bind(), listen() and accept().
#include <sys/socket.h> // For socket(), bind(), listen() and accept().
#include <unistd.h> // For close().
#include <errno.h> // For error handling.
#include <netinet/in.h> // For struct sockaddr_in and htons().
#include <string.h> // For memset().

using namespace std;



int bamSock() {

    int serverFd;

    serverFd = socket(AF_INET, SOCK_STREAM, 0);
    if (serverFd == -1) {
        return errno;
    }
    else {
        return serverFd;
    }

};

int bamBind(int serverFd,int portNumber) {

    struct sockaddr_in serverAddress;
    int bindReturnValue;

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(portNumber); // Host to network short.
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    memset(serverAddress.sin_zero, '\0', sizeof serverAddress.sin_zero); // Zero this if you want to.

    bindReturnValue = bind(serverFd, (struct sockaddr *)&serverAddress, sizeof serverAddress);
    if (bindReturnValue == -1) {
        return errno;
    }
    return 1;
};

int bamListen (int serverFd, int backlogValue) {
    int listenRetunValue = listen(serverFd,backlogValue);
    if (listenRetunValue == -1) {
        return errno;
    }
    return 1;
};

int bamAccept (int serverFd) {
    struct sockaddr_in clientAddress;
    //int sizeOfSockaddrIn = sizeof(struct sockaddr_in);
    socklen_t clilen;
    int clientFd;
    //clientFd = accept(serverFd, (struct sockaddr *)&clientAddress, &sizeOfSockaddrIn))
    clientFd = accept(serverFd, (struct sockaddr *)&clientAddress, &clilen);
    if (clientFd == -1) {
        return -1;
    }
    else {
        return clientFd;
    }
};

void bamClose(int serverFd) {

    close(serverFd);

};

#endif // BAMSOCKET_H
