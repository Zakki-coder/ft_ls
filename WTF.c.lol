#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

extern int errno;

void error_exit(void)
{
	printf("%s\n", strerror(errno));
	exit (-1);
}

int main(void)
{
	DIR *directoryp;
	struct dirent *filep;

	directoryp = opendir("Dummy_dir");
	if (!directoryp)
		error_exit();
	filep = readdir(directoryp);
	filep = readdir(directoryp);
	filep = readdir(directoryp);
	printf("EMT: %s\n", filep->d_name);
	return (0);
}