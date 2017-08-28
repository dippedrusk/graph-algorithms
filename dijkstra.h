
/* Header file
 * Implementation of Dijkstra's algorithm
 * August 28th, 2017
 */

#ifndef _DIJKSTRA_H
#define _DIJKSTRA_H

void Dijkstra(int sourcenode);
bool validNeighbour(int i, int j);
int * newPriorityQueueFromEdgeMatrix(int sourcenode);
void changeDistance(int key, int newDistance);
int extractMinDistance(void);
bool allNodesVisited(void);
void printOptimalPaths(int curr_node);

#endif
