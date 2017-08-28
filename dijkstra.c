
/* Source
 * Implementation of Dijkstra's algorithm
 * August 28th, 2017
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "dijkstra.h"

#define INFINITY 0xFFFF

extern int N, M;
extern int * edge_matrix;
extern char ** node_list;
int * previous;
int * distances;

void Dijkstra(int sourcenode)
{
  distances = newPriorityQueueFromEdgeMatrix(sourcenode); // Sets source distance to 0 and rest to infinity
  previous = malloc(N * sizeof(int));
  for (int i = 0; i < N; i++)
  {
    previous[i] = (i == sourcenode) ? sourcenode : -1; // Previous node in optimal path undefined
  }

  while(!allNodesVisited())
  {
    int nextNode = extractMinDistance();
    for (int j = 0; j < N; j++)
    {
      if (validNeighbour(nextNode, j))
      {
        int newPathLength = distances[nextNode] + edge_matrix[nextNode*N + j];
        if (newPathLength < distances[j])
        {
          changeDistance(j, newPathLength);
          previous[j] = nextNode;
        }
      }
    }
  }

  printf("Printing optimal paths:\n");
  for(int i = 0; i < N; i++)
  {
    printOptimalPaths(i);
    printf("\n");
  }

  free(distances);
  free(previous);
}

bool validNeighbour(int i, int j)
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

int * newPriorityQueueFromEdgeMatrix(int sourcenode)
{
  int * p_queue = malloc(N * sizeof(int));
  assert(p_queue);
  for (int i = 0; i < N; i++)
  {
    p_queue[i] = (i == sourcenode) ? 0 : INFINITY;
  }
  return p_queue;
}

void changeDistance(int key, int newDistance)
{
  assert(key < N);
  assert(newDistance < INFINITY);
  distances[key] = newDistance;
}

int extractMinDistance(void)
{
  int i;
  int min = INFINITY;
  int min_index = -1; // returns -1 if distances is empty
  for (i = 0; i < N; i++)
  {
    if (distances[i] != -1 && distances[i] <= min)
    {
      min = distances[i];
      min_index = i;
    }
  }
  distances[min_index] = -1;
  return min_index;
}

bool allNodesVisited(void)
{
  bool empty = true;
  for (int i = 0; i < N; i++)
  {
    if (distances[i] != -1)
    {
      empty = false;
    }
  }
  return empty;
}

void printOptimalPaths(int curr_node)
{
  printf("%s", node_list[curr_node]);
  if (previous[curr_node] != curr_node)
  {
    printf(" <= ");
    printOptimalPaths(previous[curr_node]);
  }
}
