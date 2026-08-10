OUTPUT = test
MUNIT_DIR = ./../../munit

.PHONY: build test

build:
	cc -std=c99 -Wall -Wextra intStack.c $(MUNIT_DIR)/munit.c tests.c -o $(OUTPUT)

test: build
	./$(OUTPUT)

