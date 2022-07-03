# COMPILER AND FLAGS ---------------------------------------

CC     = gcc
CFLAGS = -g -Wall -Wextra --std=c11 -pedantic


# DIRECTORIES ----------------------------------------------

BIN_DIR      = bin
OBJ_DIR      = obj
SRC_DIR      = src
TEST_DIR     = tests
TEST_BIN_DIR = $(TEST_DIR)/bin


# LIBRARIES ------------------------------------------------

CRITERION = -lcriterion


# FILES ----------------------------------------------------

# Executable
BIN = $(BIN_DIR)/PROG

# Source files
SRC = $(wildcard $(SRC_DIR)/*.c)

# Object files
OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))

# Tests source files
TESTS = $(wildcard $(TEST_DIR)/*.c)

# Tests object files (exclude main.c from test objects)
TEST_OBJ = $(subst $(OBJ_DIR)/main.o,,$(OBJ))

# Tests executables
TEST_BIN = $(patsubst $(TEST_DIR)/%.c, $(TEST_BIN_DIR)/%, $(TESTS))


# RULES ----------------------------------------------------

# Objects separated compilation
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Executable linkage from object files
$(BIN): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@

# Tests executables linkage
$(TEST_BIN_DIR)/%: $(TEST_DIR)/%.c
	$(CC) $(CFLAGS) $< $(TEST_OBJ) -o $@ $(CRITERION)

# [make]       Compile
all: $(BIN)

# [make test]  Compile and run tests
test: $(TEST_BIN)
	for test in $(TEST_BIN) ; do ./$$test ; done

# [make clean] Remove objects files and executables
clean:
	rm -f $(OBJ_DIR)/*.o $(BIN_DIR)/* $(TEST_BIN_DIR)/*

