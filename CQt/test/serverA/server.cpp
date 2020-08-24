#include "server.h"
#include "ui_server.h"

#include <stdio.h> // For perror().
#include <sys/types.h> // For socket(), bind(), listen() and accept().
#include <sys/socket.h> // For socket(), bind(), listen() and accept().
#include <netinet/in.h> // For struct sockaddr_in and htons().
#include <string.h> // For memset().
#include <stdlib.h> // For exit().
#include <arpa/inet.h> // For inet_ntop().
#include <unistd.h> // For close().


server::server(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::server)
{
    ui->setupUi(this);
    ui->label->setText("Server");

    int serverFd, clientFd, portNumber = 3000, backlogValue = 5, sizeOfSockaddrIn; // backlogValue is used in listen().
    struct sockaddr_in serverAddress, clientAddress;
    char ip4[INET_ADDRSTRLEN]; //This variable is used in third and forth arguments of inet_ntop().
    socklen_t clilen; // For accept() error: no matching function for call to 'accept'. Used in accet instead of sizeOfSockaddrIn.

    if ((serverFd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket() perror");
        exit(EXIT_FAILURE);
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

    sizeOfSockaddrIn = sizeof(struct sockaddr_in); //Get the third argument of accept().

    if ((clientFd = accept(serverFd, (struct sockaddr *)&clientAddress, &clilen)) == -1) {
        perror("accept() perror");
        exit(EXIT_FAILURE);
    }

    ::close(serverFd);

}

server::~server()
{
    delete ui;
}


