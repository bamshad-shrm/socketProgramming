#include <stdio.h> // For perror(). 
#include <sys/types.h> // For socket() and connect().
#include <sys/socket.h> // For socket() and connect().
#include <stdlib.h> // For exit().
#include <netinet/in.h> // For struct sockaddr_in and htons().
#include <string.h> // For memset().
#include <unistd.h> // For close().

#define MAXDATASIZE 100

int main() {

	int clientFd, portNumber = 3000, recvReturnValue, sendReturnValue;
	char sendData[MAXDATASIZE]="client message",receiveData[MAXDATASIZE];
	struct sockaddr_in serverAddress;

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

	while (1) {
		puts("-----------------------------------------------\n");
		printf("Enter your message\n");

		if( fgets (sendData, MAXDATASIZE, stdin) == NULL ) {
			puts("fgets error");
		}
		
		if ((sendReturnValue = send(clientFd,sendData,strlen(sendData), 0)) == -1) {
			perror("send() perror");
			exit(EXIT_FAILURE);
		}

		if ((recvReturnValue = recv(clientFd,receiveData,MAXDATASIZE-1, 0)) == -1) {
			perror("recv() perror");
			exit(EXIT_FAILURE);
		}

		receiveData[recvReturnValue] = '\0';

		printf ("sendData: %s\n",sendData);	

		printf("receiveData: %s\n" , receiveData);


	}	

	close(clientFd);
	return(0);

}












