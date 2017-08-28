
/* Will eventually contain an implementation of Dijkstra's algorithm
 * that will work on graphs that are inputted at runtime
 */

#include <stdio.h>
#include <strings.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <ctype.h>
#include <math.h>

#define BUFFER_SIZE 0xFFF
#define MAX_NUMBER_NODES 0xFF
#define MAX_EDGE_WEIGHT 0xFF
#define NODE_NAME_MAX_LENGTH 32

int N, M;
int * edge_matrix;
char ** node_list;
int declaredEdges;

int directed, weighted, scanf_ret, excessscanf_ret;

void getParameters(void);
int getInputInt(char * message, int lowerbound, int upperbound, char * inputtype);
bool getInputString(char * message, unsigned int max_size, char * string_ptr);
void getNextEdge(int i, int j);

int main(void)
{
  printf("Welcome to dijkstra.c!\n");

  directed = getInputInt("For an undirected graph, type 0. For a directed graph, type 1.", 0, 1, "options");
  weighted = getInputInt("For an unweighted graph, type 0. For a weighted graph, type 1.", 0, 1, "options");

  getParameters();

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
      printf("%d\t", edge_matrix[i*N + j]);
    }
    printf("\n");
  }
  printf("\n");

  // Didn't forget to free shit this time!
  for (int i = 0; i < N; i++)
  {
    free(node_list[i]);
  }
  free(edge_matrix);
  free(node_list);

  printf("Success!\n");
  return 0;
}

void getParameters()
{
  char excess_buffer [BUFFER_SIZE];

  N = getInputInt("Type in the number of nodes in the graph.", 1, MAX_NUMBER_NODES, "range");

  int max_edges = (directed) ? (N * (N-1)) : ((N * (N-1))/2) ;

  M = getInputInt("Type in the number of edges in the graph.", 0, max_edges, "range");

  // Allocating edges and nodes dynamically
  int edge_matrix_size = N*N;
  edge_matrix = (int *) malloc(edge_matrix_size * sizeof(int));
  assert(edge_matrix);
  node_list = (char **) malloc(N * sizeof(char*));
  assert(node_list);
  for (int i = 0; i < N; i++)
  {
    node_list[i] = (char *) malloc(32 * sizeof(char));
    assert(node_list[i]);
  }

  char message_buffer [BUFFER_SIZE];
  printf("Type in names for your %d nodes.\n", N);
  for (int i = 0; i < N; i++)
  {
    bool unique;
    do
    {
      unique = true;
      sprintf(message_buffer, "Node %d:", i+1);
      int noNames = getInputString(message_buffer, NODE_NAME_MAX_LENGTH, node_list[i]);
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

  for (int i = 0; i < N; i++)
  {
    for (int j = 0; j < N; j++)
    {
      edge_matrix[i*N +j] = (M == max_edges) ? 1 : -1;
    }
  }

  declaredEdges = (M == max_edges) ? M : 0;
  int i, j;
  while (declaredEdges != M)
  {
    for (i = 0; i < N; i++)
    {
      for (j = 0; j < N; j++)
      {
        if (declaredEdges >= M)
        {
          break;
        }
        if (i < j || i > j)
        {
          getNextEdge(i, j);
        }
      }
    }
    if (declaredEdges < M)
    {
      printf("You have declared %d of %d edges. Try again!\n", declaredEdges, M);
    }
  }

}

void getNextEdge(int i, int j)
{
  if ((edge_matrix[i*N + j]) == -1) // i.e., not yet changed
  {
    char message_buffer [BUFFER_SIZE];
    sprintf(message_buffer, "Type 1 if there is an edge between node %d [%s] and %d [%s], otherwise type 0:", i+1, node_list[i], j+1, node_list[j]);
    int result = getInputInt(message_buffer, 0, 1, "options");
    if (result)
    {
      int weight;
      if (weighted)
      {
        sprintf(message_buffer, "Type the weight of the edge between node %d [%s] and %d [%s]:", i+1, node_list[i], j+1, node_list[j]);
        weight = getInputInt(message_buffer, 0, MAX_EDGE_WEIGHT, "range");
      }
      edge_matrix[i*N + j] = (weighted) ? weight : result;
      declaredEdges++;
      printf("[Edge %d of %d]: %s -> %s\n", declaredEdges, M, node_list[i], node_list[j]);
      if (!directed)
      {
        edge_matrix[j*N + i] = (weighted) ? weight : result;
        declaredEdges++;
        printf("[Edge %d of %d]: %s -> %s\n", declaredEdges, M, node_list[j], node_list[i]);
      }
    }
  }
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
    int sscanf_ret = sscanf(input_buffer, "%u%s", &ret, excess_buffer);
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
          memcpy(string_ptr, excess_buffer, NODE_NAME_MAX_LENGTH);
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
