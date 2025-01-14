#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "global.h"
#include "http_server.h"

#ifdef __linux__
    #include <arpa/inet.h>
    #define ARPA_IS_INCLUDED
#endif

static int SERVER_SOCKET = 0;
static LISTEN_CALLBACK_FUNCTION LISTEN_CALLBACK = NULL;

static void server_listen();

void server_start (int portnum, LISTEN_CALLBACK_FUNCTION callback)
{
	#ifdef ARPA_IS_INCLUDED
		printf("ARPA INCLUDED.\nStarting program.\n");
	#else
		#error "ARPA library not included".
		exit(-1);
	#endif

	// Attempts to create the server's socket
	SERVER_SOCKET = socket(AF_INET, SOCK_STREAM, 0);

	LISTEN_CALLBACK = callback;

	if(SERVER_SOCKET == -1)
	{
		perror("FAILED IN CREATING SERVER SOCKET");
		exit(-2);
	}

	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = INADDR_ANY;

	// Convert and attributes bytes for one that is network usable
	server_address.sin_port = htons(portnum);

	socklen_t server_len = sizeof(server_address);

	// Attemps to bind the server's socket
	int socket_bind_result = bind(SERVER_SOCKET, (struct sockaddr *) &server_address, server_len);

	if(socket_bind_result == -1)
	{
		perror("ERROR ON BINDING SERVER SOCKET");
		exit(-3);
	}

	// Makes server listen for incoming connections
	if(listen(SERVER_SOCKET, 10) == -1)
	{
		perror("SERVER ERROR WHEN ATTEMPTING TO LISTEN TO PORT:");
		perror((char*) PORT);
		exit(-4);
	}

	printf("Listening on PORT %d \n\n", portnum);

	// Listen to request
	while(true)
    {
		server_listen();
    }

	close(SERVER_SOCKET);
}

static void server_listen ()
{
	struct sockaddr_in client_address;
    socklen_t client_len = sizeof(&client_address);

    // Accepts a connection from a client
    int client_socket = accept(SERVER_SOCKET, (struct sockaddr*) &client_address, &client_len);

	if(client_socket == -1)
    {
        perror("FAILED TO ACCEPT REQUEST FROM CLIENT");
        exit(-5);
    }

	// Converts and store an IP address to a string
    char* client_from = inet_ntoa(client_address.sin_addr);
    // Converts from network to host
    int client_port = ntohs(client_address.sin_port);

    printf("\nAccepted connection from %s, PORT: %d \n", client_from, client_port);

	HTTP_REQUEST req = client_http_request(client_socket);

	set_client_socket(client_socket);

	// Calls the set callback function
	if(LISTEN_CALLBACK != NULL)
	{
		LISTEN_CALLBACK(req);
	}

	invoke_router(req);

	close(client_socket);
}
