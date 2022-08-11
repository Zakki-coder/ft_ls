#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/xattr.h>
#include <sys/acl.h>

extern int errno;

void error_exit(void)
{
	printf("%s\n", strerror(errno));
	exit (-1);
}
	/*listxatrr and getxattr */

int main(void)
{
	ssize_t size;
	char *namebuf;
	void *value;
	acl_t acl;

	errno = 0;
	acl = acl_get_link_np("../../", ACL_TYPE_EXTENDED);	
	if (acl)
		printf("Jee +++++\n");
	acl_free((void *)acl);
	/*
	size = listxattr("../../Library", NULL, 0, XATTR_NOFOLLOW);
	namebuf = malloc(size + 1);
	listxattr("../../Library", namebuf, size, XATTR_NOFOLLOW);
	printf("Size: %ld, namebuf: %s\n", size, namebuf);
	free(namebuf);
	size = getxattr("../../-dc", namebuf, NULL, 0, 0, XATTR_NOFOLLOW);
	printf("ERRNO: %s and %d\n", strerror(errno), errno);
	printf("Size: %ld\n", size);
	*/
	return (0);
}