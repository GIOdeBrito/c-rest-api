#include <stdio.h>
#include <string.h>
#include "global.h"
#include "server.h"

#ifdef __linux__
    #include <arpa/inet.h>
    #define ARPA_IS_INCLUDED
#endif

static HTTPrawdata http_data = {
	.request_protocol = "HTTP/2"
};

char* http_code_description(HTTP_CODE);

void set_client_socket (int client_socket)
{
	http_data.socket = client_socket;
}

void http_html_response (HTTP_CODE code, char* content)
{
	http_data.code = code;
	http_data.content_type = "text/html";
	//http_data.socket = client_socket;
	http_data.content = content;

	send_response();
}

void http_json_response (HTTP_CODE code, char* content)
{
	http_data.code = code;
	http_data.content_type = "application/json";
	//http_data.socket = client_socket;
	http_data.content = content;

	send_response();
}

void send_response (void)
{
	char* http_response_strings[] = {
		http_data.request_protocol,
		" ",
		http_code_description(http_data.code),
		" ",
		"\r\n",
		"Content-Type: ",
		http_data.content_type,
		"\r\n\r\n",
		http_data.content
	};

	// Gets the complete char length of the response
	size_t response_char_length = string_array_content_length(http_response_strings, LENGTH(http_response_strings));
	char response[response_char_length];

	string_merge(http_response_strings, response, LENGTH(http_response_strings));

	send(http_data.socket, response, sizeof(response), 0);
}

char* http_code_description (HTTP_CODE code)
{
	switch(code)
	{
		case HTTP_OK:
			return "200 OK";
		case HTTP_ACCEPTED:
			return "202 Accepted";
		case HTTP_NOTFOUND:
			return "404 Not Found";
		default:
			return "NOT_FOUND";
	}
}
