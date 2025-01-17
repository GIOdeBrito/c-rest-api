#define MAX_JSON_KVP_LENGTH 128

typedef enum VAR_TYPE_ENUM {
    INT_FLAG,
    LONGINT_FLAG,
    FLOAT_FLAG,
    DOUBLE_FLAG,
    CONST_STRING_FLAG,
    STRING_FLAG,
    CHAR_FLAG,
    BOOLEAN_FLAG
} TYPE_FLAG;

typedef struct JSON_STRUCT {
    const char* key;
    void* value;
    TYPE_FLAG type;
} JSON;

void json_prepare(void);
void json_add(const char*,void*,TYPE_FLAG);
void json_stringify(void);
size_t json_size(void);
void json_clear(void);
void json_copyto(char*);
