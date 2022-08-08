#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

extern int errno;

typedef struct s_test
{
	int n1;
	int n2;
}	t_test;

void error_exit(void)
{
	printf("%s\n", strerror(errno));
	exit (-1);
}

int main(void)
{
	t_test *linear_array;	
	t_test **arrayp;

	linear_array = (t_test *)malloc(sizeof(*linear_array) * 4);
	bzero(linear_array, sizeof(*linear_array) * 4);
	arrayp = &linear_array;
	linear_array[0].n1 = 1;
	linear_array[0].n2 = 2;
	linear_array[1].n1 = 3;
	linear_array[1].n2 = 4;
	linear_array[2].n1 = 5;
	linear_array[2].n2 = 6;
		printf("%d\n", linear_array->n1);
		printf("%d\n", linear_array->n2);
		++linear_array;
		printf("%d\n", linear_array->n1);
		printf("%d\n", linear_array->n2);
		++linear_array;
		printf("%d\n", linear_array->n1);
		printf("%d\n", linear_array->n2);
		++linear_array;
		printf("%p\n", linear_array);
	return (0);
}