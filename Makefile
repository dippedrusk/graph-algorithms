SHELL = /bin/sh

CC = gcc
CFLAGS = -Wall

graph_headers = graph_input.h

dijkstras_src = dijkstra.c graph_input.c
prims_src = prim.c graph_input.c
kruskals_src = kruskal.c graph_input.c
bellmanford_src = bellmanford.c graph_input.c

.PHONY : all
all : dijkstra prim kruskal bellmanford

dijkstra : $(dijkstras_src) $(graph_headers)
	@echo "Compiling Dijkstra's code"
	@$(CC) $(CFLAGS) -o $@ $(dijkstras_src)

prim : $(prims_src) $(graph_headers)
	@echo "Compiling Prim's code"
	@$(CC) $(CFLAGS) -o $@ $(prims_src)

kruskal : $(kruskals_src) $(graph_headers)
	@echo "Compiling Kruskal's code"
	@$(CC) $(CFLAGS) -o $@ $(kruskals_src)

bellmanford : $(bellmanford_src) $(graph_headers)
	@echo "Compiling Bellman-Ford code"
	@$(CC) $(CFLAGS) -o $@ $(bellmanford_src)

.PHONY : clean

clean :
	@echo "Removing all executables"
	@rm -f dijkstra
	@rm -f prim
	@rm -f kruskal
	@rm -f bellmanford
