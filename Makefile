CC = gcc
CFLAGS = -Wall

programs = dijkstra test
.PHONY: all
all : $(programs)
$(programs) :
	$(CC) $(CFLAGS) -o $@ $@.c
