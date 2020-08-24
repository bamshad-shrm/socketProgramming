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

	/*
	int send(int sockfd, const void *msg, int len, int flags)

	Arguments:
	1. sockfd is the socket descriptor you want to send data to (whether it's the one returned by socket() or the one you got with accept().)
	2. msg is a pointer to the data you want to send.
	3. len is the ""LENGTH"" of that data in bytes and therefore, you can use strlen(sendData).
	4. Just set flags to 0. (See the send() man page for more information concerning flags.)
	
	Return value:
	send() returns the number of bytes actually sent out—this might be less than the number you told it to send! 
	See, sometimes you tell it to send a whole gob of data and it just can't handle it. 
	It'll fire off as much of the data as it can, and trust you to send the rest later. 
	Remember, if the value returned by send() doesn't match the value in len, it's up to you to send the rest of the string. 
	The good news is this: if the packet is small (less than 1K or so) it will probably manage to send the whole thing all in one go. 
	Again, -1 is returned on error, and errno is set to the error number.
	*/
	
	if ((sendReturnValue = send(clientFd,sendData,strlen(sendData), 0)) == -1) {
		perror("send() perror");
		exit(EXIT_FAILURE);
	}

	/*
	int recv(int sockfd, void *buf, int len, int flags)

	Arguments:
	1. sockfd is the socket descriptor to read from.
	2. buf is the buffer to read the information into.
	3. len is the ""MAXIMUM"" length of the buffer and therefore, you ""MUST"" use: your defined maximum data size - 1. 
	4. flags can again be set to 0. (See the recv() man page for flag information.)

	Retun value:
	recv() returns the number of bytes actually read into the buffer, or -1 on error (with errno set, accordingly.)
	Wait! recv() can return 0. This can mean only one thing: 
	the remote side has closed the connection on you! A return value of 0 is recv()'s way of letting you know this has occurred.
	*/

	if ((recvReturnValue = recv(clientFd,receiveData,MAXDATASIZE-1, 0)) == -1) {
		perror("recv() perror");
		exit(EXIT_FAILURE);
	}

	printf ("\nsendData: %s\n",sendData);	
	printf ("strlen(sendData): %ld\n",strlen(sendData));	
	printf ("sendReturnValue: %d\n",sendReturnValue);	

	printf("receiveData: %s\n" , receiveData);
	printf ("strlen(receiveData): %ld\n",strlen(receiveData));	
	printf("recvReturnValue: %d\n\n",recvReturnValue);
	
	close(clientFd);
	return(0);

}












