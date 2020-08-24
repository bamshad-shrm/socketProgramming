#include <stdio.h> // For perror(). 
#include <sys/types.h> // For socket() and connect().
#include <sys/socket.h> // For socket() and connect().
#include <stdlib.h> // For exit().
#include <netinet/in.h> // For struct sockaddr_in and htons().
#include <string.h> // For memset().
#include <unistd.h> // For close().

int main() {

	int clientFd, portNumber = 3000;
	struct sockaddr_in serverAddress;

	if ((clientFd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		perror("socket() perror");
		exit(EXIT_FAILURE);
	} 

	/*
	int connect(int sockfd, struct sockaddr *serv_addr, int addrlen); 

	Arguments:
	1. sockfd is our friendly neighborhood socket file descriptor, as returned by the socket() call.
	2. serv_addr is a struct sockaddr containing the destination port and IP address.
	3. ddrlen is the length in bytes of the server address structure.

	Return value:
	It'll return -1 on error and set the variable errno.
	*/

	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons(portNumber); // Host to network short.    
	serverAddress.sin_addr.s_addr = INADDR_ANY;
	memset(serverAddress.sin_zero, '\0', sizeof serverAddress.sin_zero); // Zero this if you want to.

	if (connect(clientFd, (struct sockaddr *)&serverAddress, sizeof(struct sockaddr_in)) == -1) {
		perror("connect() perror");
		exit(EXIT_FAILURE);
	}

	close(clientFd);
	return(0);

}












