
/* Will eventually contain an implementation of Dijkstra's algorithm
 * that will work on graphs that are inputted at runtime
 */

#include <stdio.h>
#include <strings.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

#define EXCESS_BUFFER_SIZE 0xFFF

int N, M;
int * edge_matrix;
char ** node_list;

int directed, weighted, scanf_ret;
char excess_buffer [EXCESS_BUFFER_SIZE];

void getParameters(void);

int main(void)
{
  printf("Welcome to dijkstra.c!\n");

  do
	{
    printf("For an undirected graph, type 0. For a directed graph, type 1. ");
		scanf_ret = scanf("%d", &directed);
		if (!scanf_ret)
		{
			printf("This is a string! Try again.\n");
      scanf("%s", excess_buffer);
		}
    else if (!(directed == 1 || directed == 0))
    {
      printf("Please type in either 0 or 1!\n");
      scanf_ret = 0;
    }
	} while (!scanf_ret);

  do
	{
    printf("For an unweighted graph, type 0. For a weighted graph, type 1. ");
		scanf_ret = scanf("%d", &weighted);
		if (!scanf_ret)
		{
			printf("This is a string! Try again.\n");
      scanf("%s", excess_buffer);
		}
    else if (!(weighted == 1 || weighted == 0))
    {
      printf("Please type in either 0 or 1!\n");
      scanf_ret = 0;
    }
	} while (!scanf_ret);

  getParameters();

  for (int i = 0; i < N; i++)
  {
    printf("%s\n", node_list[i]);
  }

  for (int i = 0; i < N; i++)
  {
    for (int j = 0; j < N; j++)
    {
      printf("%d ", edge_matrix[i*N + j]);
    }
    printf("\n");
  }

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

  do
  {
    printf("Type in the number of nodes in the graph. ");
    scanf_ret = scanf("%d", &N);
    if (!scanf_ret)
    {
      printf("This is a string! Try again.\n");
      scanf("%s", excess_buffer);
    }
  } while (!scanf_ret);

  int max_edges = (N * (N-1)) / 2;

  do
  {
    printf("Type in the number of edges in the graph. ");
    scanf_ret = scanf("%d", &M);
    if (!scanf_ret)
    {
      printf("This is a string! Try again.\n");
      scanf("%s", excess_buffer);
    }
    else if (M > max_edges)
    {
      printf("This is too many edges. Try again.\n");
      scanf_ret = 0;
    }
  } while (!scanf_ret);

  printf("\n\n\n");
  printf("Pay no attention to everything after this.");
  printf("\n\n\n");

  N = 3;
  M = 6;

  int edge_matrix_size = N*N;
  edge_matrix = (int *) malloc(edge_matrix_size * sizeof(int));
  assert(edge_matrix);
  node_list = (char **) malloc(N * sizeof(char*));
  assert(node_list);

  for (int i = 0; i < N; i++)
  {
    node_list[i] = (char *) malloc(32 * sizeof(char));
    assert(node_list[i]);
    strcpy(node_list[i], "banana\0");
    for (int j = 0; j < N; j++)
    {
      edge_matrix[i*N +j] = -1;
    }
  }
}
