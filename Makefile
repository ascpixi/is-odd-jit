CC = gcc

CFLAGS = -Wall -Werror -fPIC

SRC_DIR = src
OBJ_DIR = obj/$(OS)

SOURCES = $(wildcard $(SRC_DIR)/*.c)
OBJECTS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SOURCES))

OUTPUT_NAME = libisodd-$(OS).a

all: $(OBJ_DIR) $(OUTPUT_NAME)

# Create object directory if it doesn't exist
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OUTPUT_NAME): $(OBJECTS)
	$(AR) rcs $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(OS_CFLAGS) -c $< -o $@

# Detect OS and set appropriate flags
ifeq ($(OS),windows)
  CC = x86_64-w64-mingw32-gcc
  AR = x86_64-w64-mingw32-ar
  OS_CFLAGS = -DWIN32 -I/usr/share/mingw-w64/include/
  LDFLAGS = -Wl,--out-implib,libisodd.a
else ifeq ($(OS),linux)
  OS_CFLAGS =
else
  $(error Unknown OS specified. Please set 'OS' to one of: 'windows', 'linux')
endif

clean:
	rm -rf $(OBJ_DIR) $(OUTPUT_NAME) $(DYNAMIC_LIB)

.PHONY: all clean
