PROJECT=bin/Main

SOURCES=src/main.c src/mylib.c
TESTS=mylib.test
INC=-Isrc/

CC=gcc
CFLAGS=-Wall -g

all: bin $(PROJECT)

$(PROJECT): $(SOURCES)
	$(CC) $(CFLAGS) $(INC) -o $@ $^

bin:
	mkdir bin

test:
	make -C tests $(TESTS)

clean:
	rm -rf bin
	make -C tests clean
