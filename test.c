#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int * modifyarr(int * array);

int main (void)
{
	int * array = NULL;
	array = modifyarr(array);
	assert(array);
}

int *  modifyarr (int * array)
{
	array = (int*) malloc(3*sizeof(int));
	array[0] = 1;
	array[1] = 17;
	array[2] = 19;
	return array;
}
