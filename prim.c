
/* Source
 * Implementation of Prim's algorithm
 * September 2nd, 2017
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

void Prim(int sourcenode);
int * newPriorityQueueFromEdgeMatrix(int sourcenode);
void changeDistance(int key, int newDistance);
int extractNodeOfMinDistanceToMST(void);
bool allNodesVisited(void);
void printOptimalPaths(int curr_node);
bool validNeighbour(int i, int j);

int main (void)
{
  printf("\nWelcome to prim.c!\n");

  getParameters(&N, &M, &directed, &weighted);
  if (directed)
  {
    printf("Prim's algorithm cannot be run on a directed graph.\n");
    return 1;
  }
  node_list = getNodeList(N);
  assert(node_list);
  edge_matrix = getGraph(N, M, directed, weighted, node_list);
  assert(edge_matrix);
  int sourcenode = getSourceNode(N, node_list);

  Prim(sourcenode);

  deleteGraph(N, edge_matrix, node_list);

  return 0;
}

void Prim(int sourcenode)
{
  distances = newPriorityQueueFromEdgeMatrix(sourcenode); // Sets source distance to 0 and rest to infinity
  assert(distances);
  previous = malloc(N * sizeof(int));
  for (int i = 0; i < N; i++)
  {
    previous[i] = (i == sourcenode) ? sourcenode : -1; // Previous node in optimal path undefined
  }

  while(!allNodesVisited())
  {
    int nextNode = extractNodeOfMinDistanceToMST();
    for (int j = 0; j < N; j++)
    {
      if (validNeighbour(nextNode, j))
      {
        int newPathLength = edge_matrix[nextNode*N + j];
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

int extractNodeOfMinDistanceToMST(void)
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
    printf(" -- ");
    printOptimalPaths(previous[curr_node]);
  }
}
