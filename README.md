# 307
Implementations of various important algorithms I learned about in CMPT 307.
Run `make` or `make all` to compile. This will produce the following executables:
* dijkstra
* prim
* kruskal
* more to come...

## Contents
* Dijkstra's algorithm (compile with `make dijkstra`)
  * dijkstra.c - Implementation of Dijkstra's single-source shortest path algorithm with a priority queue
  * graph_input.c - Graph input program
* Prim's algorithm (compile with `make prim`)
  * prim.c - Implementation of Prim's algorithm to find Minimal Spanning Trees
  * graph_input.c - Graph input program
* Kruskal's algorithm (compile with `make kruskal`)
  * kruskal.c - Implementation of Kruskal's algorithm to find Minimal Spanning Trees with the Union-Find data structures
  * graph_input.c - Graph input program
