#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include "server.h"

HTTP_REQUEST client_http_request (int client_socket)
{
	char buffer[1024];
	int tbytes = recv(client_socket, buffer, 1024, 0);

	if(tbytes < 0)
	{
		perror("RECV ERROR");
		exit(1);
	}

	buffer[tbytes] = '\0';

	//printf("%s\n", buffer);

	HTTP_REQUEST client_data = {};

	char* token = strtok(buffer, " ");
	int i = 0;

	while(token != NULL)
	{
		switch(i)
		{
			case 0: client_data.method = token; break;
			case 1: client_data.path = token; break;
			case 2: client_data.protocol = token; break;
			case 4: client_data.host = token; break;
		}

		token = strtok(NULL, " ");

		i++;
	}

	return client_data;
}

/*char* request_uri (int client_socket)
{
	recv();
}*/
