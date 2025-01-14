#define MAX_ROUTES 1024

/* Http response codes */
typedef enum HTTP_CODES_ENUM {
	HTTP_OK = 200,
	HTTP_ACCEPTED = 202,
	HTTP_NOTFOUND = 404,
} HTTP_CODE;

/* This is the message response struct */
typedef struct HTTP_RESPONSE_STRUCT {
	HTTP_CODE code;
	char* content;
	char* content_type;
	char* request_protocol;
	int socket;
} HTTP_RESPONSE_DATA;

/* A client request data */
typedef struct CLIENT_REQUEST_STRUCT_DATA {
	int socket;
	char* method;
	char* path;
	char* protocol;
	char* host;
} HTTP_REQUEST;

typedef struct ROUTE_STRUCT {
	char* method;
	char* path;
} HTTP_ROUTE;

/* The callback function to be called by the server_listen method */
typedef void (*LISTEN_CALLBACK_FUNCTION)(HTTP_REQUEST);

/* The callback function set for a route */
typedef void (*ROUTE_CALLBACK_FUNCTION)(void);

void server_start(int,LISTEN_CALLBACK_FUNCTION);

void set_client_socket(int);
void http_html_response(HTTP_CODE,char*);
void http_json_response (HTTP_CODE,char*);
void http_file_response(HTTP_CODE,char*);

HTTP_REQUEST client_http_request(int);

void add_route(char*,char*,ROUTE_CALLBACK_FUNCTION);
void invoke_router(HTTP_REQUEST);
