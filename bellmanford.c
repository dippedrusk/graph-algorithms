
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
void printOptimalPaths(int curr_node);

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
  for (int i = 0; i < N; i++) // Set all initial distances to infinity (even source)
  {
    distances[i] = (i == sourcenode) ? 0 : INFINITY;
  }
  previous = malloc(N * sizeof(int));
  assert(previous);
  for (int i = 0; i < N; i++) // Previous node in optimal path undefined
  {
    previous[i] = -1;
  }

  for (int k = 0; k < N; k++)
  {
    for (int i = 0; i < N; i++)
    {
      for (int j = 0; j < N; j++)
      {
        if (edgeExists(i, j, N, edge_matrix))
        {
          int edgeweight = edge_matrix[i*N + j];
          if ((distances[i] + edgeweight) < distances[j])
          {
            distances[j] = distances[i] + edgeweight;
            previous[j] = i;
          }
        }
      }
    }
  }

  for (int i = 0; i < N; i++)
  {
    for (int j = 0; j < N; j++)
    {
      int edgeweight = edge_matrix[i*N + j];
      if ((edgeExists(i, j, N, edge_matrix)) && ((distances[i] + edgeweight) < distances[j]))
      {
        printf("\nThe input graph has a negative cycle and so shortest paths cannot be calculated meaningfully.\n");
        return;
      }
    }
  }

  printf("Printing optimal paths:\n");
  for(int i = 0; i < N; i++)
  {
    printOptimalPaths(i);
    printf("\n");
  }

  free(previous);
  free(distances);
}

void printOptimalPaths(int curr_node)
{
  printf("%s", node_list[curr_node]);
  if ((previous[curr_node] != curr_node) && (previous[curr_node] != -1))
  {
    printf(" <= ");
    printOptimalPaths(previous[curr_node]);
  }
}
