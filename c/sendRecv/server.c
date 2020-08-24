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

	int serverFd, clientFd, portNumber = 3000, backlogValue = 5, sizeOfSockaddrIn, recvReturnValue, sendReturnValue, yes=1; 
	struct sockaddr_in serverAddress, clientAddress;
	char ip4[INET_ADDRSTRLEN], sendData[MAXDATASIZE]="server message",receiveData[MAXDATASIZE]; 

	if ((serverFd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		perror("socket() perror");
		exit(EXIT_FAILURE);
	} 

	/*
	"Sometimes, you might notice, you try to rerun a server and bind() fails, claiming "Address already in use." 
	What does that mean? 
	Well, a little bit of a socket that was connected is still hanging around in the kernel, and it's hogging the port. 
	You can either wait for it to clear (a minute or so), or add code to your program allowing it to reuse the port, like this:"

	int yes=1; 

	// lose the pesky "Address already in use" error message 
	if (setsockopt(listener,SOL_SOCKET,SO_REUSEADDR,&yes,sizeof(int)) == -1) { 
		perror("setsockopt"); 
		exit(1); 
	}
	Refrence: https://ubuntuforums.org/showthread.php?t=704600
	*/

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

	sizeOfSockaddrIn = sizeof(struct sockaddr_in); 

	if ((clientFd = accept(serverFd, (struct sockaddr *)&clientAddress, &sizeOfSockaddrIn)) == -1) {
		perror("accept() perror");
		exit(EXIT_FAILURE);
	}

	printf("\n I got a connection from (%s , %d) \n",inet_ntop(AF_INET, &(clientAddress.sin_addr), ip4, INET_ADDRSTRLEN) ,ntohs(clientAddress.sin_port));  
	
	//Note: recieve() and send() are explaiend in the client code. 
	
	if ((recvReturnValue = recv(clientFd,receiveData,MAXDATASIZE-1, 0)) == -1) {
		perror("recv() perror");
		exit(EXIT_FAILURE);
	}

	if ((sendReturnValue = send(clientFd,sendData,strlen(sendData), 0)) == -1) {
		perror("send() perror");
		exit(EXIT_FAILURE);
	}

	printf ("\nsendData: %s\n",sendData);	
	printf ("strlen(sendData): %ld\n",strlen(sendData));	
	printf ("sendReturnValue: %d\n",sendReturnValue);	

	printf("receiveData: %s\n" , receiveData);
	printf ("strlen(receiveData): %ld\n",strlen(receiveData));	
	printf("recvReturnValue: %d\n\n",recvReturnValue);

	close(serverFd);
	return 0;
}



































