#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "server.h"

static HTTP_ROUTE ROUTES[MAX_ROUTES];
static ROUTE_CALLBACK_FUNCTION ROUTE_CALLBACKS[MAX_ROUTES];
static int ROUTE_COUNT = 0;

void add_route (char* method, char* path, ROUTE_CALLBACK_FUNCTION callback)
{
	if(ROUTE_COUNT > MAX_ROUTES)
	{
		printf("Maximum number of routes exceeded\n");
		return;
	}

	HTTP_ROUTE route = {
		.method = method,
		.path = path
	};

	ROUTES[ROUTE_COUNT] = route;
	ROUTE_CALLBACKS[ROUTE_COUNT] = callback;

	ROUTE_COUNT++;
}

void invoke_router (HTTP_REQUEST req)
{
	for(int i = 0; i < ROUTE_COUNT; i++)
	{
		int res_compare = memcmp(req.path, ROUTES[i].path, strlen(req.path));

		if(res_compare != 0)
		{
			continue;
		}

		//printf("Let's mosey: %s %d\n", ROUTES[i].path, i);

		if(ROUTE_CALLBACKS[i] == NULL)
		{
			printf("Callback for %s is NULL\n", req.path);
			break;
		}

		ROUTE_CALLBACKS[i]();
		return;
	}

	http_html_response(HTTP_NOTFOUND, "404 Not Found");
}
