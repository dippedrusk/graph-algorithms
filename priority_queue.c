# Priority queue

#include <stdio.h>

/*
  As input, takes an edge matrix of size N*N, creates
  a priority queue and returns it (array of size N,
  with weights)
  Insert(p_queue, key, Distance) - special case of ChangePriority
  ChangePriority(p_queue, key, newDistance)
  int ExtractMin(p_queue) - returns position of minimum, distance easy to check

  Implement extractMin so that it does an O(N) minimum every time
  instead of maintaining a sorted p_queue
*/
