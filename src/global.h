#define PORT 8080
#define LENGTH(x) sizeof(x) / sizeof(x[0])

typedef enum boolean { false, true } bool;

void string_merge(char*[],char*,int);
size_t string_array_content_length(char*[],int);
