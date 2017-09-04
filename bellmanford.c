
/* Source
 * Implementation of Bellman-Ford algorithm
 * August 28th, 2017
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "graph_input.h"

#define INFINITY 0xFFFF

int N, M, directed, weighted;
int * edge_matrix;
char ** node_list;
int * previous;
int * distances;

void BellmanFord(int sourcenode);

int main (void)
{
 printf("\nWelcome to bellmanford.c!\n");

 getParameters(&N, &M, &directed, &weighted);
 node_list = getNodeList(N);
 assert(node_list);
 bool negativeEdgesOkay = true;
 edge_matrix = getGraph(N, M, directed, weighted, node_list, negativeEdgesOkay);
 assert(edge_matrix);
 int sourcenode = getSourceNode(N, node_list);

 BellmanFord(sourcenode);

 deleteGraph(N, edge_matrix, node_list);

 return 0;
}

void BellmanFord(int sourcenode)
{
  distances = malloc(N * sizeof(int));
  assert(distances);
  for (int i = 0; i < N; i++) // Set source distance to 0 and rest to infinity
  {
    distances[i] = (i == sourcenode) ? 0 : INFINITY;
  }
  previous = malloc(N * sizeof(int));
  assert(previous);
  for (int i = 0; i < N; i++) // Previous node in optimal path undefined
  {
    previous[i] = (i == sourcenode) ? sourcenode : -1;
  }

  // meat of the algorithm

  free(previous);
  free(distances);
}
