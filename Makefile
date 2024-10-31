# Makefile for the Wish Shell Project without CUnit

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g

# Directories
SRC_DIR = src
TEST_DIR = src/tests

# Source files and object files
SRCS = $(SRC_DIR)/main.c $(SRC_DIR)/shell.c $(SRC_DIR)/parser.c $(SRC_DIR)/execute.c $(SRC_DIR)/builtins.c  $(SRC_DIR)/mish.c

OBJS = $(SRC_DIR)/shell.o $(SRC_DIR)/parser.o $(SRC_DIR)/execute.o $(SRC_DIR)/builtins.o $(SRC_DIR)/mish.o 

# Header files
HEADERS = $(SRC_DIR)/mish.h $(SRC_DIR)/shell.h $(SRC_DIR)/parser.h $(SRC_DIR)/execute.h $(SRC_DIR)/builtins.h

# Test source files and executables
TEST_SRCS = $(TEST_DIR)/test_parser.c $(TEST_DIR)/test_builtins.c
TEST_EXES = test_parser test_builtins

# Default target
all: mish

# Build the main executable
mish: $(OBJS) $(SRC_DIR)/main.o
	$(CC) $(CFLAGS) -o mish $(OBJS) $(SRC_DIR)/main.o

# Compile object files
$(SRC_DIR)/main.o: $(SRC_DIR)/main.c $(HEADERS)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/main.c -o $(SRC_DIR)/main.o

$(SRC_DIR)/shell.o: $(SRC_DIR)/shell.c $(HEADERS)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/shell.c -o $(SRC_DIR)/shell.o

$(SRC_DIR)/parser.o: $(SRC_DIR)/parser.c $(HEADERS)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/parser.c -o $(SRC_DIR)/parser.o

$(SRC_DIR)/execute.o: $(SRC_DIR)/execute.c $(HEADERS)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/execute.c -o $(SRC_DIR)/execute.o

$(SRC_DIR)/builtins.o: $(SRC_DIR)/builtins.c $(HEADERS)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/builtins.c -o $(SRC_DIR)/builtins.o

# Build test_parser executable
test_parser: $(TEST_DIR)/test_parser.o $(OBJS)
	$(CC) $(CFLAGS) -o test_parser $(TEST_DIR)/test_parser.o  $(OBJS)

# Compile test_parser.o
$(TEST_DIR)/test_parser.o: $(TEST_DIR)/test_parser.c $(HEADERS)
	$(CC) $(CFLAGS) -c $(TEST_DIR)/test_parser.c -o $(TEST_DIR)/test_parser.o

# Build test_builtins executable
test_builtins: $(TEST_DIR)/test_builtins.o $(OBJS)
	$(CC) $(CFLAGS) -o test_builtins $(TEST_DIR)/test_builtins.o $(OBJS)

# Compile test_builtins.o
$(TEST_DIR)/test_builtins.o: $(TEST_DIR)/test_builtins.c $(HEADERS)
	$(CC) $(CFLAGS) -c $(TEST_DIR)/test_builtins.c -o $(TEST_DIR)/test_builtins.o

tests: test_parser test_builtins

# Run all tests
run_tests: test
	./test_parser
	./test_builtins

# Clean up generated files
clean:
	rm -f mish $(SRC_DIR)/*.o $(TEST_EXES) $(TEST_DIR)/*.o

# Phony targets (not associated with files)
.PHONY: all clean test run_tests

