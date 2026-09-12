# Part II: complete this Makefile.
# Requirements are given in the handout.

CC = gcc
CFLAGS = -Wall -Wextra -g

# Build the stats program by default.
stats: main.o stats.o
	$(CC) $(CFLAGS) -o stats main.o stats.o

# TODO: rules for main.o and stats.o with correct header dependencies
main.o: main.c stats.h
	$(CC) $(CFLAGS) -c main.c
stats.o: stats.c stats.h
	$(CC) $(CFLAGS) -c stats.c

# TODO: clean target
clean:
	rm -f stats main.o stats.o
