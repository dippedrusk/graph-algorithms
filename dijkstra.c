
/* Will eventually contain an implementation of Dijkstra's algorithm
 * that will work on graphs that are inputted at runtime
 */

#include <stdio.h>
#include <strings.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <math.h>

#define BUFFER_SIZE 0xFFF
#define MAX_NUMBER_NODES 0xFF
#define NODE_NAME_MAX_LENGTH 32

int N, M;
int * edge_matrix;
char ** node_list;

int directed, weighted, scanf_ret, excessscanf_ret;

void getParameters(void);
int getInputInt(char * message, int lowerbound, int upperbound, char * inputtype);
void getInputString(char * message, unsigned int max_size, char * string_ptr);

int main(void)
{
  char excess_buffer [BUFFER_SIZE];
  printf("Welcome to dijkstra.c!\n");

  directed = getInputInt("For an undirected graph, type 0. For a directed graph, type 1.", 0, 1, "options");
  weighted = getInputInt("For an unweighted graph, type 0. For a weighted graph, type 1.", 0, 1, "options");

  getParameters();

  printf("Printing nodes:\n");
  for (int i = 0; i < N; i++)
  {
    printf("%s\n", node_list[i]);
  }

  printf("Printing edges:\n");
  for (int i = 0; i < N; i++)
  {
    for (int j = 0; j < N; j++)
    {
      printf("%d ", edge_matrix[i*N + j]);
    }
    printf("\n");
  }

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

  /* Things to implement:
  * Shortcut for fully connected unweighted graph?
  * How to specify edges? Program prompt or user input?
  */
  char excess_buffer [BUFFER_SIZE];

  N = getInputInt("Type in the number of nodes in the graph.", 1, MAX_NUMBER_NODES, "range");

  int max_edges = (directed) ? (N * (N-1)) : ((N * (N-1))/2) ;

  M = getInputInt("Type in the number of nodes in the graph.", 0, max_edges, "range");

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

  printf("Type in names for your %d nodes (maximum 31 characters, no spaces).\n", N);

  /*
  GARBAGE CODE (to be fixed):
  */
  for (int i = 0; i < N; i++)
  {
    printf("Node %d: ", i+1);
    assert(fgets(excess_buffer, 32, stdin) != NULL); // input to buffer
    memcpy(node_list[i], excess_buffer, 32 * sizeof(char)); // trying to copy 32 characters over
    node_list[i][strcspn(node_list[i], "\n")] = 0; // replacing /n from fgets with /0
  }
  // Code works with non-newline whitespace. Still don't know how to deal with buffer overflows.

  for (int i = 0; i < N; i++)
  {
    for (int j = 0; j < N; j++)
    {
      edge_matrix[i*N +j] = (M == max_edges) ? 1 : -1;
    }
  }
}

int getInputInt(char * message, int lowerbound, int upperbound, char * inputtype)
{
  char input_buffer [BUFFER_SIZE];
  char excess_buffer [BUFFER_SIZE];
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
    assert(fgets(input_buffer, 32, stdin) != NULL); // input to buffer
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

  return ret;
}

void getInputString(char * message, unsigned int max_size, char * string_ptr)
{
  // input_buffer[strcspn(input_buffer, "\n")] = 0; // replacing /n from fgets with /0
}
