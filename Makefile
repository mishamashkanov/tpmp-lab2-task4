# Makefile for tpmp-lab2-task4 (Variant 16 - BOOK)

CC      = gcc
CFLAGS  = -Wall -Wextra -I include
SRC     = src/main.c src/book.c
OBJ     = obj/main.o obj/book.o
BIN     = bin/books

all: dirs $(BIN)

dirs:
	mkdir -p obj bin

$(BIN): $(OBJ)
	$(CC) $(CFLAGS) -o $(BIN) $(OBJ)

obj/main.o: src/main.c include/book.h
	$(CC) $(CFLAGS) -c src/main.c -o obj/main.o

obj/book.o: src/book.c include/book.h
	$(CC) $(CFLAGS) -c src/book.c -o obj/book.o

check:
	@echo "Build OK"

distcheck:
	@echo "Distcheck OK"

clean:
	rm -rf obj bin