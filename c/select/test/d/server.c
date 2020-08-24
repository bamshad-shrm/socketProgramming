#include <stdio.h> // For perror(). 
#include <sys/types.h> // For socket(), bind(), listen() and accept().
#include <sys/socket.h> // For socket(), bind(), listen() and accept().
#include <netinet/in.h> // For struct sockaddr_in and htons().
#include <string.h> // For memset().
#include <stdlib.h> // For exit().
#include <arpa/inet.h> // For inet_ntop().
#include <unistd.h> // For close().
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

#define MAXDATASIZE 100

int main() {

	int serverFd, clientFd, portNumber = 3006, backlogValue = 5, sizeOfSockaddrIn, recvReturnValue, sendReturnValue, fdMax, selectRtnVlu; 
	// fdMax is the biggest file descriptor. 
	// selectRtnVlu is used for return value of the select function.
	struct sockaddr_in serverAddress, clientAddress;
	char ip4[INET_ADDRSTRLEN], receiveData[MAXDATASIZE]; 
	fd_set readFds, tempReadFds;	// Read file descriptor list.

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

 	FD_ZERO(&readFds); // Clear our read file descriptor list
	FD_SET(serverFd, &readFds); // Add our server to the read file descriptor list.
	fdMax = serverFd;

	while (1) {

		tempReadFds = readFds; 		

		// Start of select function.
		selectRtnVlu = select(fdMax+1, &tempReadFds, NULL, NULL, NULL); 

		if (selectRtnVlu == -1) {
			perror("select()");
		}

		if(FD_ISSET(serverFd, &tempReadFds)) {
	
			sizeOfSockaddrIn = sizeof(struct sockaddr_in); 

			if ((clientFd = accept(serverFd, (struct sockaddr *)&clientAddress, &sizeOfSockaddrIn)) == -1) {
		        perror("accept() perror");
		        continue;
		    }
			else {
				FD_SET(clientFd, &readFds); // Add the clinet fd to the read file descriptor set.
				if (fdMax < clientFd) {
					fdMax = clientFd;	// Update fdMax.
				}
			}

			printf("\n I got a connection from (%s , %d) \n",inet_ntop(AF_INET, &(clientAddress.sin_addr), ip4, INET_ADDRSTRLEN) ,ntohs(clientAddress.sin_port));
			printf(" Current fdMax: %d\n",fdMax);
			printf(" The new client fd: %d\n",clientFd);
				
		}  

		for (int i=4; i<=fdMax; i++){

			if(FD_ISSET(i, &tempReadFds)) {				

				if ((recvReturnValue = recv(i,receiveData,MAXDATASIZE-1, 0)) <= 0) {

					if (recvReturnValue == 0) {
						puts("\n The client with fd=4 is disconnected\n");
					}

					else {
						perror("recv() perror");
					}
			
					close(i);

					// bye! if we do not close it then, the clientFd and maxFd increase eache time the current client disconnects and new one arrives.
					FD_CLR(i, &readFds); // Remove from the set.

					fdMax = fdMax - 1;
				}

				else {
					receiveData[recvReturnValue] = '\0';
					for (int j=4; j<=fdMax; j++) {

						if ((sendReturnValue = send(j,receiveData,strlen(receiveData), 0)) == -1) {
							perror("send() perror");
						}

					}

				}

			}

		}

	}
	close(serverFd);
	return 0;
}



































