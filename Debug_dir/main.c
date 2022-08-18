#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <strings.h>

int main(void)
{
	int fd_our;
	int fd_your;
	char buf_our[70000];
	char buf_your[70000];

	bzero(buf_our, 70000);
	bzero(buf_your, 70000);
	fd_our = open("our", O_RDONLY);
	fd_your = open("your", O_RDONLY);
	read(fd_our, buf_our, 69999);	
	read(fd_your, buf_your, 69999);	
	printf("RET: %d\n", strcmp(buf_our, buf_your));
	return (0);
}
