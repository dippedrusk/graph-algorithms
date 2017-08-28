SHELL = /bin/sh

CC = gcc
CFLAGS = -Wall

graphs_headers = dijkstra.h graphs.h
graphs_src = driver.c dijkstra.c

test_src = test.c

.PHONY : all
all : graphs test

graphs : $(graphs_src) $(graphs_headers)
	$(CC) $(CFLAGS) -o $@ $(graphs_src)

test : $(test_src)
	$(CC) $(CFLAGS) -o $@ $(test_src)
