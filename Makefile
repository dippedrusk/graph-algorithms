SHELL = /bin/sh

CC = gcc
CFLAGS = -Wall

dijsktras_headers = graph_input.h
dijkstras_src = dijkstra.c graph_input.c

test_src = test.c

.PHONY : all
all : dijkstra test

dijkstra : $(dijkstras_src) $(dijsktras_headers)
	$(CC) $(CFLAGS) -o $@ $(dijkstras_src)

test : $(test_src)
	$(CC) $(CFLAGS) -o $@ $(test_src)
