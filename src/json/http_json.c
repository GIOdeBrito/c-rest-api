#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "json.h"
#include "../main.h"
#include "../utility/strings.h"

static JSON json[MAX_JSON_KVP_LENGTH];

static int JSON_KVP_COUNT;
static char* JSON_PARSED;

void json_prepare (void)
{
	JSON_KVP_COUNT = 0;
	json_clear();
}

void json_add (const char* key, void* value, TYPE_FLAG flag)
{
	if(JSON_KVP_COUNT > MAX_JSON_KVP_LENGTH)
	{
		perror("JSON KEY-VALUE LIMIT REACHED");
		exit(EXIT_FAILURE);
	}

	json[JSON_KVP_COUNT] = (JSON) {
		.key = key,
		.value = value,
		.type = flag
	};

	JSON_KVP_COUNT++;
}

void json_stringify (void)
{
	char* json_parsed = "{";

	int length = JSON_KVP_COUNT;
	size_t flen = 0;

	for(int i = 0; i < length; i++)
	{
		TYPE_FLAG flag = json[i].type;
		const char* key = json[i].key;

		// The buffer for the current values
		char buffer[1024];

		switch(flag)
		{
			case INT_FLAG:
			{
				int num = *(int*) json[i].value;

				// Converts the integer to a string
				// Max integer is 2147483647
				char intstr[10];
				int_tostring(num, intstr);

				snprintf(buffer, strlen(intstr) + strlen(key) + 6, "\"%s\":%s", key, intstr);
			}
			break;
			case FLOAT_FLAG:
			{
				float num = *(float*) json[i].value;

				// Converts the float to a string
				char floatstr[1024];
				float_tostring(num, floatstr);

				snprintf(buffer, strlen(floatstr) + strlen(key) + 6, "\"%s\":%s", key, floatstr);
			}
			break;
			case STRING_FLAG:
			{
				char* str = (char*) json[i].value;
				//printf("\"%s\":\"%s\"\n", key, str);

				size_t len = strlen(str) + strlen(key);
				//printf("%zu", len);

				snprintf(buffer, len + 6, "\"%s\":\"%s\"", key, str);
			}
			break;
			case BOOLEAN_FLAG:
			{
				unsigned int boolean = *(unsigned int*) json[i].value;
				snprintf(buffer, 1024, "\"%s\":\"%d\"", key, boolean);
			}
			break;
			default: {
				printf("To implement\n");
			}
			break;
		}

		flen = flen + LENGTH(buffer) + 1;

		//printf("%zu", flen);

		// Temporarily stores the parsed string
		char current_string[flen];
		strcpy(current_string, json_parsed);

		// More memory is reallocated for the JSON
		json_parsed = malloc(flen);

		if(json_parsed == NULL)
		{
			perror("COULD NOT ALLOCATE MEMORY FOR PARSED STRING");
			exit(EXIT_FAILURE);
		}

		strcpy(json_parsed, current_string);

		// Inserts a comma if there are still more items to come
		if((i + 1) < length)
		{
			strcat(buffer, ",");
		}

		// Concatenates the buffer to the parsed string
		strcat(json_parsed, buffer);
	}

	// Finishes the JSON with the last bracket
	strcat(json_parsed, "}");

	printf("%s", json_parsed);

	JSON_PARSED = malloc(flen);

	strcpy(JSON_PARSED, json_parsed);

	// Frees the allocated string from memory
	free(json_parsed);
}

size_t json_size (void)
{
	return strlen(JSON_PARSED) + 1;
}

void json_clear (void)
{
	if(JSON_PARSED != NULL)
	{
		free(JSON_PARSED);
	}

	JSON_PARSED = NULL;
}

void json_copyto (char* output)
{
	sprintf(output, "%s", JSON_PARSED);
}
