#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "strings.h"
#include "../main.h"

void string_merge (char* strings[], char* destinystring, int length)
{
	if(length == 1)
	{
		perror("AT LEAST TWO STRINGS ARE REQUIRED TO MERGE");
		return;
	}

	size_t full_length = string_array_content_length(strings, length);

	char* merged_string = malloc(full_length);

	if(merged_string == NULL)
	{
		perror("FAILED TO MERGE STRINGS");
		exit(EXIT_FAILURE);
	}

	strcpy(merged_string, strings[0]);

	for(int i = 1; i < length; i++)
	{
		strcat(merged_string, strings[i]);
	}

	//printf("%s\n", merged_string);

	snprintf(destinystring, full_length, "%s", merged_string);

	free(merged_string);
}

size_t string_array_content_length (char* strings[], int length)
{
	size_t full_length = 1;

	for(int i = 0; i < length; i++)
	{
		full_length += strlen(strings[i]);
	}

	return full_length;
}

void int_tostring (int value, char* out)
{
    sprintf(out, "%d", value);
}

void float_tostring (float value, char* out)
{
    sprintf(out, "%1.3f", value);
}
