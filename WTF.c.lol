#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

extern int errno;

void error_exit(void)
{
	printf("%s\n", strerror(errno));
	exit (-1);
}

int main(void)
{
	ssize_t link_size;
	char buf[1024];

	bzero(buf, 1024);
	link_size = readlink("thelink", buf, 1024);
	printf("Size: %ld, buf: %s\n", link_size, buf);
	link_size = readlink("helmix", buf, 1024);
	printf("Size: %ld, buf: %s\n", link_size, buf);
	return (0);
}