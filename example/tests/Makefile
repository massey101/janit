
# Describes what we are going to test
TESTS = mylib.min.test mylib.test

# Add the file we are going to test and the unit file
# Also we will need to include the header files in the src directory.
MYLIB_SOURCES = ../src/mylib.c mylib.test.c
MYLIB_MIN_SOURCES = ../src/mylib.c mylib.min.test.c
INC = -I../src/

INC += -I../../ # janit.h would normall be in the current directory
# and therefore wouldn't be needed

CC=gcc
CFLAGS=-Wall -g

all: $(TESTS)

mylib.test: $(MYLIB_SOURCES)
	$(CC) $(CFLAGS) $(INC) -o $@ $^
	./$@

mylib.min.test: $(MYLIB_MIN_SOURCES)
	$(CC) $(CFLAGS) $(INC) -o $@ $^
	./$@

clean:
	rm -f $(TESTS)
