#include <stdio.h> // For perror(). 
#include <sys/types.h> // For socket() and connect().
#include <sys/socket.h> // For socket() and connect().
#include <stdlib.h> // For exit().
#include <netinet/in.h> // For struct sockaddr_in and htons().
#include <string.h> // For memset().
#include <unistd.h> // For close().

#define MAXDATASIZE 100

int main() {

	int clientFd, portNumber = 3005, recvReturnValue, sendReturnValue;
	char sendData[MAXDATASIZE]="client message",receiveData[MAXDATASIZE];
	struct sockaddr_in serverAddress;
	fd_set fds; // Set the file descriptor list.

	if ((clientFd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		perror("socket() perror");
		exit(EXIT_FAILURE);
	} 

	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons(portNumber);    
	serverAddress.sin_addr.s_addr = INADDR_ANY;
	memset(serverAddress.sin_zero, '\0', sizeof serverAddress.sin_zero);

	if (connect(clientFd, (struct sockaddr *)&serverAddress, sizeof(struct sockaddr_in)) == -1) {
		perror("connect() perror");
		exit(EXIT_FAILURE);
	}

	FD_ZERO(&fds); // Clear the set of descriptors.

	while (1) {

		FD_SET(0, &fds); // Add Keyboard	to set of descriptors.
		FD_SET(clientFd,&fds); // Add our Socket fd to the set of descriptors.

		// Note: fdMax = clientFd because it is client and the fd numbers does not increase. 
		if (select(clientFd+1, &fds, NULL, NULL, NULL) == -1) {
			perror("select() perror");
			exit(EXIT_FAILURE);
        }

		// Looking if there is a user input from keyboard (0 is for stdin).
		if (FD_ISSET(0,&fds)) { 

			if (fgets (sendData, MAXDATASIZE, stdin) == NULL ) {
				puts("fgets error");
			}

			if ((sendReturnValue = send(clientFd,sendData,strlen(sendData), 0)) == -1) {
				perror("send() perror");
				exit(EXIT_FAILURE);
			}

		}

		// Looking if there is a message from server.
		if (FD_ISSET(clientFd,&fds)) { 

			if ((recvReturnValue = recv(clientFd,receiveData,MAXDATASIZE-1, 0)) == -1) {
				perror("recv() perror");
				exit(EXIT_FAILURE);
			}

			receiveData[recvReturnValue] = '\0';
	
			printf("receiveData: %s\n" , receiveData);

		}

	}	

	close(clientFd);
	return(0);

}












