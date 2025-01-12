#include <stdio.h>
#include "global.h"
#include "server.h"

void create_routes (void);
void callback (HTTP_REQUEST);
void route_root (void);
void route_time (void);
void route_timev2 (void);

int main (void)
{
	printf("REST API Starting\n\n");

	create_routes();
	server_start(PORT, callback);

	printf("Shutting down\n");

	return 0;
}

void create_routes (void)
{
	add_route("GET", "/", route_root);
	add_route("GET", "/time", route_time);
	add_route("GET", "/timev2", route_timev2);
}

void callback (HTTP_REQUEST req)
{
	printf("%s\n", req.method);
	printf("%s\n", req.path);
	printf("%d\n", req.socket);
}

void route_root (void)
{
	http_html_response(HTTP_OK, "REST API");
}

void route_time (void)
{
	http_html_response(HTTP_OK, "It's time to du- du- du- du- dududududuel!");
}

void route_timev2 (void)
{
	http_html_response(HTTP_OK, "<h1>Higi'a ha-zman le-du-karav</h1>");
}
