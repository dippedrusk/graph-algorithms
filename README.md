# Graph Algorithms
C implementations of various important algorithms in graph theory for shortest paths and minimal spanning trees. Run `make` or `make all` to compile. This will produce the following executables:
* dijkstra (`make dijkstra`)
* prim (`make prim`)
* kruskal (`make kruskal`)
* bellmanford (`make bellmanford`)

Then run them the regular way, e.g., `./dijsktra` or optionally with one of the provided sample graphs like so - `./prim < samplegraph1.txt`

## Contents
* Source
  * graph_input.c - Graph input code that is a common dependency for all the other driver files
  * dijkstra.c - Implementation of Dijkstra's single-source shortest path algorithm with a priority queue
  * prim.c - Implementation of Prim's algorithm to find minimal spanning trees
  * kruskal.c - Implementation of Kruskal's algorithm to find minimal spanning trees with the Union-Find data structure
  * bellmanford.c - Implementation of Bellman-Ford single-source shortest path algorithm with negative edges
* Sample graphs
  * samplegraph1.txt
    * Undirected weighted graph to test with Dijkstra's, Prim's, Kruskal's and Bellman-Ford
    * Illustrates that shortest paths and minimal spanning trees are not the same problem because Dijkstra's and Bellman-Ford give a different result from Prim's and Kruskal's
  * samplegraph2.txt
    * Directed graph with negative weights and a negative cycle to test with Bellman-Ford
    * Shows that Bellman-Ford can detect a negative cycle
    * Running Dijkstra's on this sample graph will break it because the graph input program loops till it gets a non-negative edge weight
    * Prim's and Kruskal's do not run on directed graphs
  * samplegraph3.txt
    * Directed graph with negative weights with no negative cycle to test with Bellman-Ford
    * Outputs shortest paths with negative weights since there is no negative cycle
    * Does not run with Dijkstra's, Prim's and Kruskal's for the reasons described above

## Time Complexity
N = number of nodes, M = number of edges

* Graph input program: O(N^2)
* Dijkstra's algorithm: O(N^2)
  * newPriorityQueue: O(N)
  * Main loop executes O(N) times because it runs until every node is visited
    * allNodesVisited: O(N)
    * extractMinDistance: O(N)
    * Inner for loop executes O(N) times because it checks for an edge with every node
      * validNeighbour: O(1)
      * changeDistance: O(1)
    * changeDistance: O(1)
* Prim's algorithm: O(N^2)
  * This algorithm is implemented almost exactly like Dijkstra's and thus has the same time complexity
* Kruskal's algorithm: O(M*N^2)
  * newUnionFind: O(N)
  * Main loop executes O(M) times because it runs until every edge is visited
    * allEdgesVisited: O(N^2)
    * Inner loops run in O(N^2)
    * Find: O(1)
    * Union: O(N)
    * deleteEdge: O(1)
* Bellman-Ford algorithm: O(N^3)
  * Initializing distances and previous arrays: O(N)
  * Main loop executes O(N^3) times
  * The loop to check for negative cycles runs in O(N^2)
