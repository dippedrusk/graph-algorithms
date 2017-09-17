
/* Graph input source
 * Takes and validates an input graph and returns to any driver program that
 * calls it
 * August 27th, 2017
 */

#include <stdio.h>
#include <strings.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <ctype.h>
#include <math.h>
#include "graph_input.h"

#define BUFFER_SIZE 0xFFF
#define MAX_NUMBER_NODES 0xFF

#define MIN_NEG_EDGE_WEIGHT -255
#define MIN_NONNEG_EDGE_WEIGHT 0
#define MAX_EDGE_WEIGHT 255
#define NODE_NAME_MAX_LENGTH 32

#define EDGE_DOES_NOT_EXIST -500

int declaredEdges;

void getParameters(int * N_ptr, int * M_ptr, int * directed_ptr, int * weighted_ptr)
{
  int directed = getInputInt("\nFor an undirected graph, type 0. For a directed graph, type 1.", 0, 1, "options");
  int weighted = getInputInt("\nFor an unweighted graph, type 0. For a weighted graph, type 1.", 0, 1, "options");

  int N = getInputInt("\nType in the number of nodes in the graph.", 1, MAX_NUMBER_NODES, "range");

  int max_edges = (directed) ? (N * (N-1)) : ((N * (N-1))/2) ;

  int M = getInputInt("\nType in the number of edges in the graph.", 0, max_edges, "range");

  *directed_ptr = directed;
  *weighted_ptr = weighted;
  *N_ptr = N;
  *M_ptr = M;
}

char ** getNodeList(int N)
{
  char ** node_list = (char **) malloc(N * sizeof(char*));
  assert(node_list);
  for (int i = 0; i < N; i++)
  {
    node_list[i] = (char *) malloc(32 * sizeof(char));
    assert(node_list[i]);
  }

  char message_buffer [BUFFER_SIZE];
  printf("\nType in names for your %d nodes.\n", N);
  for (int i = 0; i < N; i++)
  {
    bool unique;
    do
    {
      unique = true;
      sprintf(message_buffer, "Node %d:", i+1);
      bool noNames = getInputString(message_buffer, NODE_NAME_MAX_LENGTH, node_list[i]);
      if (noNames)
      {
        sprintf(node_list[i], "%d", i+1);
      }
      for (int j = 0; j < i; j++)
      {
        if (strcmp(node_list[i], node_list[j]) == 0)
        {
          printf("This node name has already been used for node %d. Try again.\n", j+1);
          unique = false;
        }
      }
    } while(!unique);
  }

  return node_list;
}

int * getGraph(int N, int M, int directed, int weighted, char ** node_list, bool negativeEdgesOkay)
{
  int edge_matrix_size = N * N;
  int * edge_matrix = (int *) malloc(edge_matrix_size * sizeof(int));
  assert(edge_matrix);

  for (int i = 0; i < N; i++)
  {
    for (int j = 0; j < N; j++)
    {
      edge_matrix[i*N +j] = EDGE_DOES_NOT_EXIST;
    }
  }

  declaredEdges = 0;
  int i, j;
  for (i = 0; i < N; i++)
  {
    for (j = 0; j < N; j++)
    {
      if (declaredEdges >= M)
      {
        break;
      }
      if ((i != j) && (!edgeExists(i, j, N, edge_matrix))) // i.e., not yet changed
      {
        char message_buffer [BUFFER_SIZE];
        sprintf(message_buffer, "Type 1 if there is an edge between node %d [%s] and %d [%s], otherwise type 0:", i+1, node_list[i], j+1, node_list[j]);
        int weight = getInputInt(message_buffer, 0, 1, "options");
        if (weight)
        {
          if (weighted)
          {
            sprintf(message_buffer, "Type the weight of the edge between node %d [%s] and %d [%s]:", i+1, node_list[i], j+1, node_list[j]);
            if (negativeEdgesOkay)
            {
              weight = getInputInt(message_buffer, MIN_NEG_EDGE_WEIGHT, MAX_EDGE_WEIGHT, "range");
            }
            else
            {
              weight = getInputInt(message_buffer, MIN_NONNEG_EDGE_WEIGHT, MAX_EDGE_WEIGHT, "range");
            }
          }
          edge_matrix[i*N + j] = weight;
          printf("[Edge %d of %d]: %s -> %s\n\n", ++declaredEdges, M, node_list[i], node_list[j]);
          if (!directed)
          {
            edge_matrix[j*N + i] = weight;
          }
        }
      }
    }
  }
  if (declaredEdges < M)
  {
    printf("You have declared %d of %d edges. Try again!\n\n", declaredEdges, M);
    free(edge_matrix);
    edge_matrix = getGraph(N, M, directed, weighted, node_list, negativeEdgesOkay);
  }

  printf("\nEdge matrix for your graph:\n");
  printf("\n\t");
  for (int i = 0; i < N; i++)
  {
    printf("%s\t", node_list[i]);
  }
  printf("\n");
  for (int i = 0; i < N; i++)
  {
    printf("%s\t", node_list[i]);
    for (int j = 0; j < N; j++)
    {
      if (edgeExists(i, j, N, edge_matrix))
      {
        printf("%d\t", edge_matrix[i*N + j]);
      }
      else
      {
        printf("%s\t", "NA");
      }
    }
    printf("\n");
  }
  printf("\n");

  return edge_matrix;
}

int getInputInt(char * message, int lowerbound, int upperbound, char * inputtype)
{
  char * input_buffer = malloc(BUFFER_SIZE * sizeof(char));
  assert(input_buffer);
  char * excess_buffer = malloc(BUFFER_SIZE * sizeof(char));
  assert(excess_buffer);
  bool validInput = false;

  // - ignore all whitespace
  // - raise error for strings
  // - error for too many characters (of any kind)
  // - error for no input
  // - within bounds

  int ret;

  do
  {
    printf("%s ", message);
    assert(fgets(input_buffer, BUFFER_SIZE, stdin) != NULL); // input to buffer
    int sscanf_ret = sscanf(input_buffer, "%d%s", &ret, excess_buffer);
    switch (sscanf_ret)
    {
      case -1: // No input
        printf("You have not typed a value.\n");
        break;
      case 0: // Not a number
        printf("You have not typed a number.\n");
        break;
      case 1: // Ret value has been assigned - bounds check
        if (strcmp(inputtype, "options") == 0 && ret != lowerbound && ret != upperbound)
        {
          printf("The value '%d' is not %d or %d\n", ret, lowerbound, upperbound);
        }
        else if (strcmp(inputtype, "range") == 0 && (ret < lowerbound || ret > upperbound))
        {
          printf("The value '%d' is not between %d and %d\n", ret, lowerbound, upperbound);
        }
        else
        {
          validInput = true;
        }
        break;
      case 2: // There is an int followed by other characters
        printf("You have typed other characters after\n");
        break;
    }
  } while (!validInput);

  free(input_buffer);
  free(excess_buffer);
  return ret;
}

bool getInputString(char * message, unsigned int max_size, char * string_ptr)
{
  char * input_buffer = malloc(BUFFER_SIZE * sizeof(char));
  assert(input_buffer);
  char * excess_buffer = malloc(BUFFER_SIZE * sizeof(char));
  assert(excess_buffer);
  bool validInput = false;
  bool noNames = false;

  // - ignore all whitespace
  // - lower case entire string
  // - no input -> default (handle later)
  // - within bounds

  do
  {
    printf("%s ", message);
    assert(fgets(input_buffer, BUFFER_SIZE, stdin) != NULL);
    int sscanf_ret = sscanf(input_buffer, "%s", excess_buffer);
    switch (sscanf_ret)
    {
      case -1: // No input
        noNames = true;
        validInput = true;
        break;
      case 0: // Not a number
        printf("You have not typed a string.\n");
        break;
      case 1: // Ret value has been assigned - bounds check
        if (strlen(excess_buffer) > max_size)
        {
          printf("Your input is too long. It can be no bigger than %d characters.\n", max_size);
        }
        else
        {
          strcpy(string_ptr, excess_buffer);
          for (int i = 0; i < strlen(string_ptr); i++)
          {
            string_ptr[i] = tolower(string_ptr[i]);
          }
          validInput = true;
        }
        break;
    }
  } while (!validInput);

  free(input_buffer);
  free(excess_buffer);
  return noNames;
}

int getSourceNode(int N, char ** node_list)
{
  bool valid = false;
  char sourcenode[NODE_NAME_MAX_LENGTH];
  do
  {
    bool noNames = getInputString("From which node would you like to begin running the algorithm?", NODE_NAME_MAX_LENGTH, sourcenode);
    if (noNames)
    {
      break;
    }
    for (int i = 0; i < N; i++)
    {
      if (strcmp(node_list[i], sourcenode) == 0)
      {
        valid = true;
        return i;
      }
    }
    printf("You have not typed in a valid node name! Try again.\n");
    printf("The following are the names of your nodes:\n");
    for (int i = 0; i < N; i++)
    {
      printf("%s\n", node_list[i]);
    }
  } while(!valid);
  return 0; // defaults to first node if no source specified
}

void deleteGraph(int N, int * edge_matrix, char ** node_list)
{
  for (int i = 0; i < N; i++)
  {
    free(node_list[i]);
  }
  free(edge_matrix);
  free(node_list);
}

bool edgeExists(int i, int j, int N, int * edge_matrix)
{
  if (edge_matrix[i*N + j] == EDGE_DOES_NOT_EXIST)
  {
    return false;
  }
  return true;
}

void deleteEdge(int i, int j, int N, int * edge_matrix)
{
  edge_matrix[i*N + j] = EDGE_DOES_NOT_EXIST;
}
