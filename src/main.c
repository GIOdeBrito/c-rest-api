#include <stdio.h>
#include "main.h"
#include "server/http_server.h"
#include "json/json.h"

#define PORT 8080

void create_routes (void);
void callback (HTTP_REQUEST);
void route_root (void);
void route_time (void);
void route_json (void);

int main (void)
{
	printf("REST API Starting\n\n");

	create_routes();
	server_start(PORT, callback);

	printf("Shutting down...\n");

	return 0;
}

void create_routes (void)
{
	add_route("GET", "/", route_root);
	add_route("GET", "/api/v1/time", route_time);
	add_route("GET", "/api/v1/json", route_json);
}

void callback (HTTP_REQUEST req)
{
	printf("%s\n", req.method);
	printf("%s\n", req.path);
	//printf("%d\n", req.socket);
}

void route_root (void)
{
	http_html_response(HTTP_OK, "REST API");
}

void route_time (void)
{
	http_html_response(HTTP_OK, "{\"time\":\"00:00\"}");
}

void route_json (void)
{
	json_prepare();
    json_add("name", (void*) "Giordano de Brito", STRING_FLAG);

	int age = 23;
	json_add("age", &age, INT_FLAG);
	json_add("message", (void*) "This is a JSON object generated in C!", STRING_FLAG);
	json_stringify();

	char json[json_size()];
	json_copyto(json);

	http_json_response(HTTP_OK, json);
}
