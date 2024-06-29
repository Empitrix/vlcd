#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include "utils.h"

/*
socket id (returned int) can be use for 'send' and 'read'
*/

/* return a socket id for client */
int client_soc(int port){
	int status, client_fd;
	struct sockaddr_in serv_addr;

	client_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (client_fd < 0)
		return e_return(-1, "Socket Creation Error");

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(port);


	status = inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr);
	if (status <= 0)
		return e_return(-1, "Invalid Address / Address Not Supported");

	status = connect(client_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));

	if (status < 0)
		return e_return(-1, "Connection Failed");

	return client_fd;
}



/* return a socket id for server */
int server_soc(int port){
	int server_fd, new_socket, status;
	struct sockaddr_in address;
	int opt = 1;
	socklen_t addrlen = sizeof(address);

	server_fd = socket(AF_INET, SOCK_STREAM, 0);

	if (server_fd < 0)
		return e_return(-1, "Socket Error");
		// pexit(1, "Socket Error");

	// Forcefully attaching socket to the port 8080
	status = setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));

	if (status)
		return e_return(-1, "Set Socket Option Error");
		// pexit(1, "Set Socket Option Error");

	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(port);

	status = bind(server_fd, (struct sockaddr*)&address, sizeof(address));

	if(status < 0)
		return e_return(-1, "Bind Error");
		// pexit(1, "Bind Error");

	status = listen(server_fd, 3);

	if (status < 0) 
		return e_return(-1, "Listen Error");
		// pexit(1, "Listen Error");

	new_socket = accept(server_fd, (struct sockaddr*)&address, &addrlen);

	if (new_socket < 0)
		return e_return(-1, "Accept Error");
		// pexit(1, "Accept Error");


	close(server_fd);   // closing the listening socket

	return new_socket;
}

