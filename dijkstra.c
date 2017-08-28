
/* Will eventually contain an implementation of Dijkstra's algorithm
 * that will work on graphs that are inputted at runtime
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "dijkstra.h"
#include "priority_queue.h"

void Dijkstra(int N, int * edge_matrix, int sourcenode)
{
  int * distances = newPriorityQueueFromEdgeMatrix(N, sourcenode);
  int * previous = malloc(N * sizeof(int));


  // keep array previous[N]
  // need edge matrix and distance priority queue to run algorithm
  // define isNeighbour function
  // remember to ignore all entries of -1 in the edge matrix because that
  // is an absent edge and Dijkstra fails with negative edge weights
  free(distances);
  free(previous);
}
