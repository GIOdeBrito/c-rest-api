
# =========================================================
# REST API makefile
# =========================================================

COMPILER = gcc
CFLAGS = -Wall
HEADER = global.h http_server.h

SOURCE = 	main.c utility.c http_server.c http_response.c \
			http_utility.c http_route.c

# Object files
OBJ_DIR = objects
_OBJ = $(patsubst %.c, %.o, $(SOURCE))
OBJ = $(patsubst %, $(OBJ_DIR)/%, $(_OBJ))

# Name of the executable
PROJECT = main.g

$(OBJ_DIR)/%.o: %.c $(HEADER)
	$(COMPILER) -c -o $@ $< $(CFLAGS)

$(PROJECT): $(OBJ)
	$(COMPILER) -o $@ $^ $(CFLAGS)
