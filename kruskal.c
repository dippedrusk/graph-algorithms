
/* Source
 * Implementation of Kruskal's algorithm
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
int * unionfind;

void Kruskal(void);
int * makeUnionFindFromEdgeMatrix(void);
int Find(int u);
void Union(int u, int v);
bool allNodesVisited(void);
void printOptimalPaths(int curr_node);

int main (void)
{
 printf("\nWelcome to kruskal.c!\n");

 getParameters(&N, &M, &directed, &weighted);
 if (directed)
 {
   printf("Kruskal's algorithm cannot be run on a directed graph.\n");
   return 1;
 }
 node_list = getNodeList(N);
 assert(node_list);
 bool negativeEdgesOkay = true;
 edge_matrix = getGraph(N, M, directed, weighted, node_list, negativeEdgesOkay);
 assert(edge_matrix);

 Kruskal();

 deleteGraph(N, edge_matrix, node_list);

 return 0;
}

void Kruskal(void)
{
  unionfind = makeUnionFindFromEdgeMatrix();
  assert(unionfind);
  previous = malloc(N * sizeof(int));
  assert(previous);
  for (int i = 0; i < N; i++)
  {
    previous[i] = -1; // Previous node in optimal path undefined
  }

  while(!allNodesVisited())
  {
    int min_edge_weight = INFINITY;
    int min_i, min_j;
    for (int i = 0; i < N; i++)
    {
      for (int j = 0; j < N; j++)
      {
        int edgeweight = edge_matrix[i*N + j];
        if ((edgeweight < min_edge_weight) && (edgeweight != -1))
        {
          min_edge_weight = edge_matrix[i*N + j];
          min_i = i;
          min_j = j;
        }
      }
    }
    printf("%d %d\n", min_i, min_j);
    if (Find(min_i) != Find(min_j))
    {
      previous[min_i] = min_j;
      Union(min_i, min_j);
    }
    edge_matrix[min_i*N + min_j] = -1;
  }

  for (int i = 0; i < N; i++)
  {
    printf("%d ", previous[i]);
  }
  printf("\n\n");

  printf("Printing optimal paths:\n");
  for(int i = 0; i < N; i++)
  {
    printOptimalPaths(i);
    printf("\n");
  }

  free(unionfind);
  free(previous);
}

int * makeUnionFindFromEdgeMatrix(void)
{
  int * unionfind = malloc(N * sizeof(int));
  assert(unionfind);
  for (int i = 0; i < N; i++)
  {
    unionfind[i] = i;
  }
  return unionfind;
}

int Find(int u)
{
  assert(u < N);
  return unionfind[u];
}

void Union(int u, int v)
{
  assert(u < N);
  assert(v < N);
  int target = unionfind[u];
  for (int i = 0; i < N; i++)
  {
    if (unionfind[i] == target)
    {
      unionfind[i] = unionfind[v];
    }
  }
}

bool allNodesVisited(void)
{
  bool empty = true;
  for (int i = 0; i < N*N; i++)
  {
    if (edge_matrix[i] != -1)
    {
      empty = false;
    }
  }
  return empty;
}

void printOptimalPaths(int curr_node)
{
  printf("%s", node_list[curr_node]);
  if (previous[curr_node] != -1)
  {
    printf(" -- ");
    printOptimalPaths(previous[curr_node]);
  }
}
