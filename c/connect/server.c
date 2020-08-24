#include <stdio.h> // For perror(). 
#include <sys/types.h> // For socket(), bind(), listen() and accept().
#include <sys/socket.h> // For socket(), bind(), listen() and accept().
#include <netinet/in.h> // For struct sockaddr_in and htons().
#include <string.h> // For memset().
#include <stdlib.h> // For exit().
#include <arpa/inet.h> // For inet_ntop().
#include <unistd.h> // For close().

int main() {

	int serverFd, clientFd, portNumber = 3000, backlogValue = 5, sizeOfSockaddrIn; // backlogValue is used in listen().
	struct sockaddr_in serverAddress, clientAddress;
	char ip4[INET_ADDRSTRLEN]; //This variable is used in third and forth arguments of inet_ntop().

	/*
	int socket(int domain, int type, int protocol) 
 
	Arguments:
	1. AF_INET for IPv4, and PF_INET6 for IPv6.
	2. SOCK_STREAM for reliable TCP sockets, or SOCK_DGRAM for UDP sockets. 
	Another interesting socket type is SOCK_RAW which can be used to construct packets by hand. It's pretty cool.
	3. you can just set the protocol to 0, and it'll use the proper protocol automatically.

    Return value: 
	Simply returns to you a socket descriptor that you can use in later system calls, 
	or -1 on error. The global variable errno is set to the error's value
	*/

	if ((serverFd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		perror("socket() perror");
		exit(EXIT_FAILURE);
	} 

	/*
	int bind(int sockfd, struct sockaddr *my_addr, int addrlen) 

	Arguments:
	1. sockfd is the socket file descriptor returned by socket().
	2. my_addr is a pointer to a struct sockaddr that contains information about your address, namely, port and IP address.
	3. addrlen is the length in bytes of that address.

	Return value:
	Returns -1 on error and sets errno to the error's value.
	*/

	/*
	Set the struct sockaddr (the second argument of bind) members.
	1. AF_INET for IPv4, and PF_INET6 for IPv6.
	2. Port number.In this part we should use one of the followin functions:
	htons(), htonl(), ntohs(), ntohl()
	They Convert multi-byte integer types from host byte order to network byte order.
	Each function returns the converted value.
	The full description can be found on:
	https://beej.us/guide/bgnet/html/single/bgnet.html#htonsman
	Note: All ports below 1024 are RESERVED (unless you're the superuser)! 
	You can have any port number above that, right up to 65535 (provided they aren't already being used by another program.) 
	3. You can assign INADDR_ANY to the s_addr field if you wanted to bind to your local IP address.
	The other option is to set the ip address. For example: 
	serverAddress.sin_addr.s_addr = inet_addr("10.12.110.57");.
	4. There's also this sin_zero field in struct sockaddr_in which some people claim must be set to zero. 
	Other people don't claim anything about it (the Linux documentation doesn't even mention it at all), 
	and setting it to zero doesn't seem to be actually necessary. So, if you feel like it, set it to zero using memset().
	*/

	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons(portNumber); // Host to network short.    
	serverAddress.sin_addr.s_addr = INADDR_ANY;
	memset(serverAddress.sin_zero, '\0', sizeof serverAddress.sin_zero); // Zero this if you want to.

	if (bind(serverFd, (struct sockaddr *)&serverAddress, sizeof serverAddress) == -1) {
		perror("bind() perror");
		exit(EXIT_FAILURE);
	}

	/*
	int listen(int sockfd, int backlog)

	Arguments:
	1. sockfd is the usual socket file descriptor from the socket() system call.
	2. backlog is the number of connections allowed on the incoming queue.

	Return value:
	Returns -1 on error and sets errno to the error's value.		 
	*/

	if (listen(serverFd,backlogValue) == -1) {
		perror("listen() perror");
		exit(EXIT_FAILURE);
	}

	printf("server: waiting for connections...\n");

	/*
	int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen)
	
	Arguments:
	1. sockfd is the listen()ing socket descriptor.
	2. addr will usually be a pointer to a local struct sockaddr_storage. 
	This is where the information about the incoming connection will go (and with it you can determine which host is calling you from which port).
	3. addrlen is a local integer variable that should be set to sizeof(struct sockaddr_storage) before its address is passed to accept(). 
	accept() will not put more than that many bytes into addr. If it puts fewer in, it'll change the value of addrlen to reflect that.

	Return Value:
	It returns -1 and sets errno if an error occurs.
	*/

	sizeOfSockaddrIn = sizeof(struct sockaddr_in); //Get the third argument of accept().

	if ((clientFd = accept(serverFd, (struct sockaddr *)&clientAddress, &sizeOfSockaddrIn)) == -1) {
		perror("accept() perror");
		exit(EXIT_FAILURE);
	}

	/*
	After we got a conncetoin, we can print the IP address and port number of it.
	On the other words in this part we want to convert IP addresses to human-readable form and back.
	For this propose we can use inet_ntop() and ntohs(). 

	const char *inet_ntop(int af, const void *src,char *dst, socklen_t size);
		 
	Arguments:
	1. Takes the address family in the af parameter (either AF_INET or AF_INET6)		
	2. The src parameter should be a pointer to either a struct in_addr or struct in6_addr containing the address you wish to convert to a string.
	3. Finally dst and size are the pointer to the destination string and the maximum length of that string.
	The maximum lengths are: INET_ADDRSTRLEN and INET6_ADDRSTRLEN.

	Return value:
	Returns the dst parameter on success, or NULL on failure (and errno is set).

	Note: ntohs() is described in the bind() section.

	*/

	printf("\n I got a connection from (%s , %d)\n\n",inet_ntop(AF_INET, &(clientAddress.sin_addr), ip4, INET_ADDRSTRLEN) ,ntohs(clientAddress.sin_port)); 
 
	/*
	int close(int s);

	Description:
	After you've finished using the socket for whatever demented scheme you have concocted and you don't want to send() or recv() or, 
	indeed, do anything else at all with the socket, you can close() it, and it'll be freed up, never to be used again.

	The remote side can tell if this happens one of two ways. One: if the remote side calls recv(), it will return 0. Two: 
	if the remote side calls send(), it'll receive a signal SIGPIPE and send() will return -1 and errno will be set to EPIPE.

	Argument: 
	1. s is the usual socket file descriptor from the socket() system call.

	Return value:
	Returns zero on success, or -1 on error (and errno will be set accordingly.).
	*/

	close(serverFd);
	return 0;
}



































