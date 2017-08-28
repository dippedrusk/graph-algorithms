
/* Will eventually contain an implementation of Dijkstra's algorithm
 * that will work on graphs that are inputted at runtime
 */

#ifndef _DIJKSTRA_H
#define _DIJKSTRA_H

int * Dijkstra(int N, int * edge_matrix, int sourcenode);
bool validNeighbour(int N, int * edge_matrix, int * distances, int i, int j);

#endif
