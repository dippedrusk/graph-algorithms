
/* Contains an implementation of a priority queue used
 * in the implementation of Dijkstra's
 */

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include "priority_queue.h"

#define INFINITY 0xFFFF

int * newPriorityQueueFromEdgeMatrix(int N, int sourcenode)
{
  int * p_queue = malloc(N * sizeof(int));
  assert(p_queue);
  for (int i = 0; i < N; i++)
  {
    p_queue[i] = (i == sourcenode) ? 0 : INFINITY;
  }
  return p_queue;
}

void changePriority(int N, int * p_queue, int key, int newDistance)
{
  assert(key < N);
  assert(newDistance < INFINITY);
  p_queue[key] = newDistance;
}

int extractMin(int N, int * p_queue)
{
  int i;
  int min = INFINITY;
  int min_index = -1; // returns -1 if p_queue is empty
  for (i = 0; i < N; i++)
  {
    if (p_queue[i] != -1 && p_queue[i] <= min)
    {
      min = p_queue[i];
      min_index = i;
    }
  }
  p_queue[min_index] = -1;
  return min_index;
}

bool isEmpty(int N, int * p_queue)
{
  bool empty = true;
  for (int i = 0; i < N; i++)
  {
    if (p_queue[i] != -1)
    {
      empty = false;
    }
  }
  return empty;
}
