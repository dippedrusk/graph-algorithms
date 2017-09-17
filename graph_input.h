
/* Graph input header file
 * August 28th, 2017
 */

#ifndef _GRAPH_INPUT_H
#define _GRAPH_INPUT_H

void getParameters(int * N_ptr, int * M_ptr, int * directed_ptr, int * weighted_ptr);
char ** getNodeList(int M);
int * getGraph(int N, int M, int directed, int weighted, char ** node_list, bool negativeEdgesOkay);

int getInputInt(char * message, int lowerbound, int upperbound, char * inputtype);
bool getInputString(char * message, unsigned int max_size, char * string_ptr);
int getSourceNode(int N, char ** node_list);
bool edgeExists(int i, int j, int N, int * edge_matrix);
void deleteEdge(int i, int j, int N, int * edge_matrix);

void deleteGraph(int N, int * edge_matrix, char ** node_list);

#endif
