#include <stdio.h>
#include <string.h>
#include "global.h"
#include "http_server.h"

#ifdef __linux__
    #include <arpa/inet.h>
    #define ARPA_IS_INCLUDED
#endif

static HTTP_RESPONSE_DATA HTTP_DATA = {
	.request_protocol = "HTTP/2"
};

static void send_response(void);
static char* http_code_description(HTTP_CODE);

void set_client_socket (int client_socket)
{
	HTTP_DATA.socket = client_socket;
}

void http_html_response (HTTP_CODE code, char* content)
{
	HTTP_DATA.code = code;
	HTTP_DATA.content_type = "text/html";
	HTTP_DATA.content = content;

	send_response();
}

void http_json_response (HTTP_CODE code, char* content)
{
	HTTP_DATA.code = code;
	HTTP_DATA.content_type = "application/json";
	HTTP_DATA.content = content;

	send_response();
}

void http_file_response (HTTP_CODE code, char* filepath)
{
	HTTP_DATA.code = code;
	HTTP_DATA.content_type = "text/html";
	//HTTP_DATA.content = content;
}

static void send_response (void)
{
	char* http_response_strings[] = {
		HTTP_DATA.request_protocol,
		" ",
		http_code_description(HTTP_DATA.code),
		" ",
		"\r\n",
		"Content-Type: ",
		HTTP_DATA.content_type,
		"\r\n\r\n",
		HTTP_DATA.content
	};

	// Gets the complete char length of the response
	size_t response_char_length = string_array_content_length(http_response_strings, LENGTH(http_response_strings));

	// This variable will hold the output of the merged response
	char response[response_char_length];

	// Merge the response header with the response body
	string_merge(http_response_strings, response, LENGTH(http_response_strings));

	/* Returns the data to the client. Reducing the size of the response
	by 1 is necessary to not send the final '\0' character */
	send(HTTP_DATA.socket, response, sizeof(response) - 1, 0);
}

static char* http_code_description (HTTP_CODE code)
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
