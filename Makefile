SHELL = /bin/sh

CC = gcc
CFLAGS = -Wall

graph_headers = graph_input.h
dijkstras_src = dijkstra.c graph_input.c
prims_src = prim.c graph_input.c

test_src = test.c

.PHONY : all
all : dijkstra prim test

dijkstra : $(dijkstras_src) $(graph_headers)
	$(CC) $(CFLAGS) -o $@ $(dijkstras_src)

prim : $(prims_src) $(graph_headers)
	$(CC) $(CFLAGS) -o $@ $(prims_src)

test : $(test_src)
	$(CC) $(CFLAGS) -o $@ $(test_src)
