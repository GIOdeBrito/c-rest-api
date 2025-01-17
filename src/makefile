
# =========================================================
# REST API makefile
# =========================================================

COMPILER = 	gcc
CFLAGS = 	-Wall
HEADER = 	main.h server/http_server.h json/json.h utility/strings.h

SOURCE = 	main.c utility/strings.c server/http_server.c server/http_response.c \
			server/http_utility.c server/http_route.c json/http_json.c

# Object files
BUILD_DIR = build
_OBJ = $(patsubst %.c, %.o, $(SOURCE))
OBJ = $(patsubst %, $(BUILD_DIR)/%, $(_OBJ))

# Name of the executable
PROJECT = main.g

$(BUILD_DIR)/%.o: %.c $(HEADER)
	$(COMPILER) -c -o $@ $< $(CFLAGS)

$(PROJECT): $(OBJ)
	$(COMPILER) -o $@ $^ $(CFLAGS)
