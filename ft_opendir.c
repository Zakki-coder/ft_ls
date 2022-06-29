#include "includes/ft_ls.h"

void error_exit(void)
{
	ft_printf("%s\n", strerror(errno));
	exit (-1);
}

void get_file_type(t_file_node *node, char *permissions)
{
	int type;

	type = node->type;
	if (type & DT_DIR)
		permissions[0] = 'd';
	else if (type & DT_LNK)
		permissions[0] = 'l';
	else if (type & DT_BLK)
		permissions[0] = 'b';
	else if (type & DT_CHR)
		permissions[0] = 'c';
	else if (type & DT_SOCK)
		permissions[0] = 's';
	else if (type & DT_FIFO)
		permissions[0] = 'p';
}

void print_permissions(unsigned int st_mode, t_file_node *node)
{
	char permissions[11];

	ft_memset(permissions, '-', 10);
	permissions[10] = '\0';
	get_file_type(node, permissions);
	if (st_mode & S_IRUSR)
		permissions[1] = 'r';
	if (st_mode & S_IWUSR)
		permissions[2] = 'w';
	if (st_mode & S_IXUSR)
		permissions[3] = 'x';
	if (st_mode & S_IRGRP)
		permissions[4] = 'r';
	if (st_mode & S_IWGRP)
		permissions[5] = 'w';
	if (st_mode & S_IXGRP)
		permissions[6] = 'x';
	if (st_mode & S_IROTH)
		permissions[7] = 'r';
	if (st_mode & S_IWOTH)
		permissions[8] = 'w';
	if (st_mode & S_IXOTH)
		permissions[9] = 'x';
	ft_printf("%-10s", permissions);
}

void print_time(t_file_node *node)
{
	char *time;
	char output[27];

	ft_bzero(output, 27);
	time = ctime(&node->stat.st_mtimespec.tv_sec);
	if (!time)
		error_exit();
	time += 8;
	ft_strncpy(output, time, 3);
	time -= 4;
	ft_strncat(output, time, 4);
	time += 7;
	ft_strncat(output, time, 5);
	ft_strncat(output, " ", 1);
	ft_printf("%*s", ft_strlen(output) + 1, output);
}

unsigned int nb_len(long long nb)
{
	int len;

	len = 1;
	while (nb >= 10)
	{
		++len;
		nb /= 10;
	}
	return (len);
}
/*	TODO: Also the path/filename column should show links.
	TODO: Get terminal window width */

void print_stat(t_file_node *node, t_width *widths)
{
	struct passwd	*pw;
	struct group	*grp;

	pw = getpwuid(node->stat.st_uid);
	grp = getgrgid(node->stat.st_gid);
	if (!pw || !grp)
		error_exit();
	if (node->is_head)
		ft_printf("total %llu\n", widths->total_size);
	print_permissions(node->stat.st_mode, node);
	ft_printf("%*u", widths->link_col + 2, node->stat.st_nlink);
	ft_printf(" %-*s", (int)ft_strlen(pw->pw_name) + 2, pw->pw_name);
	ft_printf("%s", grp->gr_name);
	ft_printf("%*d ", widths->size_col + 2, node->stat.st_size);
	print_time(node);
	ft_printf("%s\n", node->file_name);
}

int main(void)
{
	t_file_node *head;
	t_width		widths;
	char path[1024] = ".";

	ft_bzero((void *)&widths, sizeof(widths));
	//TODO: Protect opendir, but first put it inside loop.
	//TODO: Remember closedir also.
	//TODO: Readdir can return for multiple reasons, use errno to decide if exit is needed
	head = create_list(opendir(path), path, &widths); 
	while (head)	
	{
		print_stat(head, &widths);
		head = head->next;
	}
	
	return (0);
}