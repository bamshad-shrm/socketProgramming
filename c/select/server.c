#include <stdio.h> // For perror(). 
#include <sys/types.h> // For socket(), bind(), listen(), accept() and select().
#include <sys/socket.h> // For socket(), bind(), listen() and accept().
#include <netinet/in.h> // For struct sockaddr_in and htons().
#include <string.h> // For memset().
#include <stdlib.h> // For exit().
#include <arpa/inet.h> // For inet_ntop().
#include <unistd.h> // For close().

#define MAXDATASIZE 100

int main() {

	int serverFd, clientFd, portNumber = 3000, backlogValue = 5, sizeOfSockaddrIn, recvReturnValue, sendReturnValue, fdMax, selectRtnVlu, yes=1; 
	// fdMax is the biggest file descriptor. 
	// selectRtnVlu is used for return value of the select function.
	struct sockaddr_in serverAddress, clientAddress;
	char ip4[INET_ADDRSTRLEN], receiveData[MAXDATASIZE]; 
	fd_set readFds, tempReadFds;	// Read file descriptor lists.

	if ((serverFd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		perror("socket() perror");
		exit(EXIT_FAILURE);
	} 

	if (setsockopt(serverFd,SOL_SOCKET,SO_REUSEADDR,&yes,sizeof(int)) == -1) { 
		perror("setsockopt"); 
		exit(1); 
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

 	FD_ZERO(&readFds); // Clear our read file descriptor list.
	FD_SET(serverFd, &readFds); // Add our server to the read file descriptor list.
	fdMax = serverFd; // Set the fdMax value as our server file descriptor.

	/* IMPORTANT!
	"On exit, each of the file descriptor sets is modified in place to
	indicate which file descriptors actually changed status. (Thus, if
	using select() within a loop, the sets must be reinitialized before
	each call.)" []
	*/

	/*
	"Notice I have two file descriptor sets in the code: master and read_fds (readFds and tempReadFds in our code). 
	The first, master (readFds), holds all the socket descriptors that are currently connected, 
	as well as the socket descriptor that is listening for new connections.

	The reason I have the master (readFds) set is that select() actually changes the set you pass into it to reflect which sockets are ready to read. 
	Since I have to keep track of the connections from one call of select() to the next, I must store these safely away somewhere. 
	At the last minute, I copy the master into the read_fds, and then call select().

	But doesn't this mean that every time I get a new connection, I have to add it to the master (readFds) set? Yup! 
	And every time a connection closes, I have to remove it from the master (readFds) set? Yes, it does.

	Notice I check to see when the listener socket is ready to read. 
	When it is, it means I have a new connection pending, and I accept() it and add it to the master (readFds) set. 
	Similarly, when a client connection is ready to read, and recv() returns 0, I know the client has closed the connection, 
	and I must remove it from the master (readFds) set.

	If the client recv() returns non-zero, though, I know some data has been received. 
	So I get it, and then go through the master (readFds) list and send that data to all the rest of the connected clients".
	Refrence: https://beej.us/guide/bgnet/html/single/bgnet.html#select
	*/

	while (1) {

		tempReadFds = readFds; 		

		// Start of select function.
		selectRtnVlu = select(fdMax+1, &tempReadFds, NULL, NULL, NULL); 

		if (selectRtnVlu == -1) {
			perror("select()");
		}

		// Monitoring the server's fd to check if something happens.

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

		for (int i=serverFd+1; i<=fdMax; i++) {

			/* 
			Monitoring the clients's fds to chek if something happens.
			Because it is possible to have more than one client we should put it insied a for loop. 
			*/

			if(FD_ISSET(i, &tempReadFds)) {				

				if ((recvReturnValue = recv(i,receiveData,MAXDATASIZE-1, 0)) <= 0) {

					if (recvReturnValue == 0) {
						printf("\n The client with fd=%d is disconnected\n",i);
					}

					else {
						perror("recv() perror");
					}
			
					close(i); // Bye!

					FD_CLR(i, &readFds); // Remove from the set.

				}

				else {
					receiveData[recvReturnValue] = '\0';
					for (int j=serverFd+1; j<=fdMax; j++) {

						if (FD_ISSET(j, &readFds)) {

							if ((sendReturnValue = send(j,receiveData,strlen(receiveData), 0)) == -1) {
								perror("send() perror");
							}

						}

					}

				}

			} // End of if(FD_ISSET(i, &tempReadFds)). 

		} // End of for (int i=serverFd+1; i<=fdMax; i++)).

	} // End of while(1).

	close(serverFd);
	return 0;

}



































