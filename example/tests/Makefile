
# Describes what we are going to test
TESTS = mylib.test

# Add the file we are going to test and the unit file
# Also we will need to include the header files in the src directory.
MYLIB_SOURCES = ../src/mylib.c mylib.test.c
INC = -I../src/

INC += -I../../ # janit.h would normall be in the current directory
# and therefore wouldn't be needed

CC=gcc
CFLAGS=-Wall -g

mylib.test: $(MYLIB_SOURCES)
	$(CC) $(CFLAGS) $(INC) -o $@ $^
	./$@

clean:
	rm -f $(TESTS)
