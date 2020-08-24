#include <stdio.h> // For perror(). 
#include <sys/types.h> // For socket(), bind(), listen() and accept().
#include <sys/socket.h> // For socket(), bind(), listen() and accept().
#include <netinet/in.h> // For struct sockaddr_in and htons().
#include <string.h> // For memset().
#include <stdlib.h> // For exit().
#include <arpa/inet.h> // For inet_ntop().
#include <unistd.h> // For close().

#define MAXDATASIZE 100

int main() {

	int serverFd, clientFd, portNumber = 3000, backlogValue = 5, sizeOfSockaddrIn, recvReturnValue, sendReturnValue; 
	struct sockaddr_in serverAddress, clientAddress;
	char ip4[INET_ADDRSTRLEN], receiveData[MAXDATASIZE]; 

	if ((serverFd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		perror("socket() perror");
		exit(EXIT_FAILURE);
	} 

	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons(portNumber);   
	serverAddress.sin_addr.s_addr = INADDR_ANY;
	memset(serverAddress.sin_zero, '\0', sizeof serverAddress.sin_zero); 

	if (bind(serverFd, (struct sockaddr *)&serverAddress, sizeof serverAddress) == -1) {
		perror("bind() perror");
		exit(EXIT_FAILURE);
	}

	if (listen(serverFd,backlogValue) == -1) {
		perror("listen() perror");
		exit(EXIT_FAILURE);
	}

	printf("server: waiting for connections...\n");

	while (1) {

		sizeOfSockaddrIn = sizeof(struct sockaddr_in); 

		if ((clientFd = accept(serverFd, (struct sockaddr *)&clientAddress, &sizeOfSockaddrIn)) == -1) {
            perror("accept() perror");
            continue;
        }

		printf("\n I got a connection from (%s , %d) \n",inet_ntop(AF_INET, &(clientAddress.sin_addr), ip4, INET_ADDRSTRLEN) ,ntohs(clientAddress.sin_port));  

		while (1) {
			
			if ((recvReturnValue = recv(clientFd,receiveData,MAXDATASIZE-1, 0)) == -1) {
				perror("recv() perror");
				exit(EXIT_FAILURE);
			}


			if (recvReturnValue == 0) {
				puts(" The client is disconnected\n");
				break;
			}

			printf("\nRecieved message: %s\n",receiveData);

			receiveData[recvReturnValue] = '\0';

			if ((sendReturnValue = send(clientFd,receiveData,strlen(receiveData), 0)) == -1) {
				perror("send() perror");
				exit(EXIT_FAILURE);
			}

		}

	}

	close(serverFd);
	return 0;
}



































