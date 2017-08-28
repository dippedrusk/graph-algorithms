
/* Will eventually contain an implementation of Dijkstra's algorithm
 * that will work on graphs that are inputted at runtime
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "dijkstra.h"
#include "priority_queue.h"

int * Dijkstra(int N, int * edge_matrix, int sourcenode)
{
  int * distances = newPriorityQueueFromEdgeMatrix(N, sourcenode); // Sets source distance to 0 and rest to infinity
  int * previous = malloc(N * sizeof(int));
  for (int i = 0; i < N; i++)
  {
    previous[i] = (i == sourcenode) ? sourcenode : -1; // Previous node in optimal path undefined
  }

  while(!isEmpty(N, distances))
  {
    int nextNode = extractMin(N, distances);
    for (int j = 0; j < N; j++)
    {
      if (validNeighbour(N, edge_matrix, distances, nextNode, j))
      {
        int newPathLength = distances[nextNode] + edge_matrix[nextNode*N + j];
        if (newPathLength < distances[j])
        {
          changePriority(N, distances, j, newPathLength);
          previous[j] = nextNode;
        }
      }
    }
  }

  free(distances);
  return previous;
}

bool validNeighbour(int N, int * edge_matrix, int * distances, int i, int j)
{
  bool valid = true;
  if (edge_matrix[i*N + j] == -1) // no edge between i and j
  {
    valid = false;
  }
  if (distances[j] == -1) // already visited node
  {
    valid = false;
  }
  return valid;
}
