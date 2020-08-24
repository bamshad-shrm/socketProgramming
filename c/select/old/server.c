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

	int serverFd, clientFd, portNumber = 3000, backlogValue = 5, sizeOfSockaddrIn, recvReturnValue, sendReturnValue,fdMax;
	// fdMax is maximum file descriptor number. 
	struct sockaddr_in serverAddress, clientAddress;
	char ip4[INET_ADDRSTRLEN], receiveData[MAXDATASIZE]; 
	fd_set fds,temp_fds; // fds is the main file descriptor list and temp_fds is a temporary file descriptor list for select().

	FD_ZERO(&fds); // Clear the main set.
	FD_ZERO(&temp_fds); // Clear the temporary set.

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

	FD_SET(serverFd, &fds); // Add server socket file descriptor (serverFd) to set of main file descriptors.
	fdMax = serverFd; //Set server socket file descriptor (serverFd) as max file descriptor number.
	// 0, 1, 2 for stdin, stdout, and stderr, and 3 is our server socket fd.
	// So, at this point fdMax is equal to 3. Later, when new clients arrive it will increases.

	while (1) {

		/*
		On exit, each of the file descriptor sets is modified in place to
		indicate which file descriptors actually changed status.  (Thus, if
		using select() within a loop, the sets must be reinitialized before
		each call.)
		*/

		temp_fds = fds;

		/*
		int select(int numfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, struct timeval *timeout)

		Arguments:
		1. The parameter numfds should be set to the values of the highest file descriptor plus one.
		2. readfds if you want to know when any of the sockets in the set is ready to recv() data.
		3. writefds if any of the sockets is ready to send() data.
		4. exceptfds if you need to know when an exception (error) occurs on any of the sockets.
		5. This time structure allows you to specify a timeout period. If you do not want it set it to NULL.
		Note: Any or all of these parameters can be NULL if you're not interested in those types of events.

		Return value:
		Returns the number of descriptors in the set on success, 0 if the timeout was reached, or -1 on error (and errno will be set accordingly.) 
		Also, the sets are modified to show which sockets are ready.
		*/

		if (select(fdMax+1, &temp_fds, NULL, NULL, NULL) == -1) {
			perror("select() perror");
			exit(EXIT_FAILURE);
        }
		   
		// Run through the connections which are already exist to look for data to be read.
		// We start the loop from 3 because, we do not want to check stdin, stdout and stderr.
		// So, we start from 3 which is our server socket fd. 
		for(int i=3;i<=fdMax;i++) {

			if(FD_ISSET(i, &temp_fds)) {

				if(i == serverFd) {

					sizeOfSockaddrIn = sizeof(struct sockaddr_in); 

					if ((clientFd = accept(serverFd, (struct sockaddr *)&clientAddress, &sizeOfSockaddrIn)) == -1) {
						perror("accept() perror");
						continue;
					}

					printf("\n I got a connection from (%s , %d) \n",inet_ntop(AF_INET, &(clientAddress.sin_addr), ip4, INET_ADDRSTRLEN) ,ntohs(clientAddress.sin_port)); 

					// Add the file descriptor of new client to the rest.
					FD_SET(clientFd, &fds);

					// keep track of the max
					if(clientFd>fdMax) {
						fdMax = clientFd;
					}
 
				}

				else {				

					if ((recvReturnValue = recv(i,receiveData,MAXDATASIZE-1, 0)) <= 0) {

						if (recvReturnValue == 0) {
							puts(" The client is disconnected\n");
						}

						else {
							perror("recv() perror");
						}

                        close(i); // bye!
                        FD_CLR(i, &fds); // Remove from main set.
					}

					else {
						// 0, 1, 2 for stdin, stdout, and stderr, and 3 is our server socket.
						for(int j = 4; j <= fdMax; j++) { 

							receiveData[recvReturnValue] = '\0';

							if ((sendReturnValue = send(j,receiveData,strlen(receiveData), 0)) == -1) {
								perror("send() perror");
							}

						}

					}

				}

			} // End of if(FD_ISSET(i, &temp_fds))

		} // End of for(int i=3;i<=fdMax;i++)

	} //End of while (1)

	close(serverFd);
	return 0;
}

































































