/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_opendir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 17:59:01 by jniemine          #+#    #+#             */
/*   Updated: 2022/08/06 18:37:51 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

void error_exit(void)
{
	ft_printf("%s\n", strerror(errno));
	exit (-1);
}

void get_file_type(t_file_node *node, char *permissions)
{
	unsigned int type;

	type = node->type;
	if (type == DT_DIR)
		permissions[0] = 'd';
	else if (type == DT_LNK)
		permissions[0] = 'l';
	else if (type == DT_BLK)
		permissions[0] = 'b';
	else if (type == DT_CHR)
		permissions[0] = 'c';
	else if (type == DT_SOCK)
		permissions[0] = 's';
	else if (type == DT_FIFO)
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

/*	On unix time, day is always 86400seconds.
	1 Month (30.44 days)	2629743 Seconds
*/
void print_time(t_file_node *node)
{
	char			*timep;
	time_t			current_time;
	char			output[27];
	long long int	time_difference;

	current_time = time(NULL);
	ft_bzero(output, 27);
	timep = ctime(&node->stat.st_mtimespec.tv_sec);
	if (!timep)
		error_exit();
	timep += 8;
	ft_strncpy(output, timep, 3);
	timep -= 4;
	ft_strncat(output, timep, 4);
	timep += 7;
	time_difference = current_time - node->stat.st_mtimespec.tv_sec;
	if (time_difference > (2629743 * 6) || (-1 * time_difference) > (2629743 * 6))
	{
		ft_strncat(output, " ", 1);
		ft_strncat(output, timep + 9, 4);
	}
	else
		ft_strncat(output, timep, 5);
	ft_strncat(output, " ", 1);
	ft_printf("%*s", ft_strlen(output), output);
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

// Changed all stat to lstat, so that links are not followed
void print_stat(t_file_node *node, t_width *widths, char **dir_paths, int *i)
{
	struct passwd	*pw;
	struct group	*grp;
	char			*name;
	char			link_buf[1024];

	ft_bzero((void *)link_buf, 1024);
	name = node->file_name;
	pw = getpwuid(node->lstat.st_uid);
	grp = getgrgid(node->lstat.st_gid);
	if (!pw || !grp)
		error_exit();
	if (node->is_head)
		ft_printf("total %llu\n", widths->total_size);
	print_permissions(node->lstat.st_mode, node);
	ft_printf("%*u", widths->link_col + 2, node->lstat.st_nlink);
	ft_printf(" %-*s", (int)ft_strlen(pw->pw_name) + 2, pw->pw_name);
	ft_printf("%s", grp->gr_name);
	ft_printf("%*d ", widths->size_col + 2, node->lstat.st_size);
	print_time(node);
	if (readlink(node->path, link_buf, 1024) > 0)
		ft_printf("%s -> %s\n", node->file_name, link_buf);
	else if (!(widths->is_file))
		ft_printf("%s\n", node->file_name);
	else
		ft_printf("%s\n", node->path);
	if (dir_paths && node->type & DT_DIR && ft_strcmp(name, ".") != 0 && ft_strcmp(name, "..") != 0)
		dir_paths[(*i)++] = node->path;
}

DIR *open_directory(char *path)
{
	DIR *dirp;

	dirp = opendir(path);
	if (!dirp && errno == ENOTDIR)
		return (NULL);
	if (!dirp && errno != ENOENT)
		error_exit();
	else if(!dirp)
		ft_printf("ft_ls: %s: %s", path, strerror(errno));
	return(dirp);
}

int main(int argc, char **argv)
{
	t_width		widths_and_flags;
	int i;
	t_file_node *head;
	t_paths		paths;
//	DIR **dirp;
//	char **dir_paths;

	i = 0;
	ft_bzero((void *)&paths, sizeof(t_paths));
	ft_bzero((void *)&widths_and_flags, sizeof(widths_and_flags));
	paths.open_dir = (DIR **)ft_memalloc(sizeof(DIR *) * argc + 1);
	paths.arg_paths = (char **)ft_memalloc(sizeof(char *) * argc + 1);
	//TODO: Protect opendir, but first put it inside loop.
	//TODO: Remember closedir also.
	//TODO: Readdir can return for multiple reasons, use errno to decide if exit is needed
	//TODO: If R flag, then we need to connect previous tail to next head.
	//TODO: You must call create list once for the starting direcotry for recursion, to get the width. 
	i = ls_get_flags(argc, argv, &widths_and_flags.flags);
	sort_arguments(argc - i, &argv[i], &widths_and_flags, paths);
	if (*paths.arg_paths)
		widths_and_flags.flags |= PRINT_DIR_NAME;
//	dirp = open_directory(argv[i]); // PROTECT
//	if (!dirp)
//		error_exit();
	while (*(paths.open_dir))
	{
		head = create_list(*paths.open_dir, *paths.arg_paths, &widths_and_flags);
		paths.dir_paths = (char **)ft_memalloc(sizeof(char *) * widths_and_flags.dir_amount + 1);
		if (widths_and_flags.flags & RECURSIVE)
		{
	//		print_loop(head, widths_and_flags, dir_paths);
			choose_output_format(head, &widths_and_flags, paths.dir_paths);
			recursive_traverse(paths.dir_paths, i, &widths_and_flags);
		}	
		else
			choose_output_format(head, &widths_and_flags, paths.dir_paths);
		free_lst(head);
		++paths.open_dir;
		++paths.arg_paths;
	}
	return (0);
}