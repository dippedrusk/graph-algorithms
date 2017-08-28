
/* Contains an implementation of a priority queue used
 * in the implementation of Dijkstra's
 */

#ifndef _PQUEUE_H
#define _PQUEUE_H

int * newPriorityQueueFromEdgeMatrix(int N, int sourcenode);
void changePriority(int N, int * p_queue, int key, int newDistance);
int extractMin(int N, int * p_queue);
bool isEmpty(int N, int * p_queue);

#endif
