
/* Header file
 * Implementation of Dijkstra's algorithm
 * August 28th, 2017
 */

#ifndef _GRAPH_INPUT_H
#define _GRAPH_INPUT_H

void getParameters(int * N_ptr, int * M_ptr, int * directed_ptr, int * weighted_ptr);
char ** getNodeList(int M);
int * getGraph(int N, int M, int directed, int weighted, char ** node_list);

int getInputInt(char * message, int lowerbound, int upperbound, char * inputtype);
bool getInputString(char * message, unsigned int max_size, char * string_ptr);
int getSourceNode(int N, char ** node_list);

void deleteGraph(int N, int * edge_matrix, char ** node_list);

#endif
