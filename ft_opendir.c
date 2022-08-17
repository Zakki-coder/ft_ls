/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_opendir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 17:59:01 by jniemine          #+#    #+#             */
/*   Updated: 2022/08/17 15:08:34 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

/* Using write here */
void error_exit(void)
{
	char *error;
	//Is write allowed???
	error = strerror(errno);
	write(STDERR_FILENO, error, ft_strlen(error));
	write(STDERR_FILENO, "\n", 1);
//	ft_printf("%s\n", strerror(errno));
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

void get_extended_permissions(t_file_node *head, char *permissions)
{
	ssize_t	size;
	acl_t	acl;
	void	*value;
	
	/* acl_get_link_np doesnt follow slink like acl_get_file */
	size = listxattr(head->path, NULL, 0, XATTR_NOFOLLOW);
	head->ext_attr_len = size;
	acl = acl_get_link_np(head->path, ACL_TYPE_EXTENDED);
	value = ft_memalloc(size);
	if (size > 0)
	{
		permissions[10] = '@';
		head->ext_attr = (char *)ft_memalloc(size + 1);
		size = listxattr(head->path, head->ext_attr, size, 0);
		head->ext_attr_p_len = getxattr(head->path, head->ext_attr, NULL, 0, 0, XATTR_NOFOLLOW);
		head->ext_attr_p_len = getxattr(head->path, head->ext_attr + ft_strlen(head->ext_attr) + 1, value, size, 0, XATTR_NOFOLLOW);
	}
	else if(acl)
	{
		head->acl = acl;
		permissions[10] = '+';
	}
	else
		permissions[10] = ' ';
}

void third_field(unsigned int st_mode, char *permissions, int i)
{
	if (!(st_mode & S_IXUSR) && ((st_mode & S_ISUID && i == 3)
		|| (st_mode & S_ISGID && i == 6)))
		*permissions = 'S';
	else if (st_mode & S_IXUSR && ((st_mode & S_ISUID && i == 3)
			|| (st_mode & S_ISGID && i == 6)))
		*permissions = 's';
	else if (st_mode & S_IXUSR)
		*permissions = 'x';
}
void print_permissions(unsigned int st_mode, t_file_node *node)
{
	char permissions[12];

	/*listxatrr and getxattr */
	ft_memset(permissions, '-', 10);
	permissions[11] = '\0';
	get_file_type(node, permissions);
	if (st_mode & S_IRUSR)
		permissions[1] = 'r';
	if (st_mode & S_IWUSR)
		permissions[2] = 'w';
	third_field(st_mode, &permissions[3], 3);
	if (st_mode & S_IRGRP)
		permissions[4] = 'r';
	if (st_mode & S_IWGRP)
		permissions[5] = 'w';
	third_field(st_mode, &permissions[6], 6);
	if (st_mode & S_IROTH)
		permissions[7] = 'r';
	if (st_mode & S_IWOTH)
		permissions[8] = 'w';
	if (!(st_mode & S_IXUSR) && st_mode & S_ISVTX)
		permissions[9] = 'T';
	else if (st_mode & S_IXUSR && st_mode & S_ISVTX)
		permissions[9] = 't';
	else
		third_field(st_mode, &permissions[9], 9);
	get_extended_permissions(node, permissions);
	ft_printf("%-10s", permissions);
}

void over_six_months(char *output, char *timep, long long int time_difference)
{
	int start;
	int len;
	
	start = 0;
	len = 0;
	if (time_difference > (2629743 * 6) || (-1 * time_difference) > (2629743 * 6))
	{
		while (timep[9 + start] && timep[9 + start] == ' ')
			++start;
		if (!timep[9 + 1])
			start = 0;
		while (timep[9 + start + len] && timep[9 + start + len] <= '9'
			&& timep[9 + start + len] >= '0')
			++len;
		ft_strncat(output, " ", 1);
		ft_strncat(output, timep + 9 + start, len);
	}
	else
		ft_strncat(output, timep, 5);
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
	timep += 4;
	ft_strncpy(output, timep, 4);
//	timep += 8;
	timep += 4;
	ft_strncat(output, timep, 3);
//	timep -= 4;
//	ft_strncat(output, timep, 4);
	timep += 3;
	time_difference = current_time - node->stat.st_mtimespec.tv_sec;
	over_six_months(output, timep, time_difference);
//	if (time_difference > (2629743 * 6) || (-1 * time_difference) > (2629743 * 6))
//	{
//		ft_strncat(output, " ", 1);
//		ft_strncat(output, timep + 9, 4);
//	}
//	else
//		ft_strncat(output, timep, 5);
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

void print_extended_attributes(t_file_node *head, int flags)
{
	int			i;
	int			tab_n;
	int			print_len;
	acl_entry_t	entryp;
	acl_permset_t permsetp;
	acl_tag_t	*tag_type;
	ssize_t		len;
//	void		*acl_qualifier;

	i = 0;
//	acl_qualifier = NULL;
	tag_type = ft_memalloc(sizeof(*tag_type));
	if(flags & EXT_ATTR && head->ext_attr)
	{
		while(i < head->ext_attr_len)	
		{
			print_len = getxattr(head->path, head->ext_attr + i, NULL, 0, 0, XATTR_NOFOLLOW);
			tab_n = ft_strlen(head->ext_attr + i) / 8;
			ft_printf("\t%s", head->ext_attr + i);
			ft_printf("%*ld\n", 13 + tab_n * 8 - ft_strlen(head->ext_attr + i), print_len);
			i += ft_strlen(head->ext_attr + i) + 1;
		}
	}
	else if(flags & ACL && head->acl)
	{
		if (acl_get_entry(head->acl, ACL_FIRST_ENTRY, &entryp) < 0)
			error_exit();
		while(entryp) 
		{
			if(acl_get_permset(entryp, &permsetp) < 0)
				error_exit();
			if(acl_get_tag_type(entryp,	tag_type) < 0)
				error_exit();
			printf("ACL: %s\n", acl_to_text(head->acl, &len));	
		//	acl_qualifier = acl_get_qualifier(entryp);
			if(acl_get_entry(head->acl, ++i, &entryp) <= 0)
				break ;
		}
	}
	/*
		acl_tag_t		ae_tag;
		uid_t			ae_id;
		acl_perm_t		ae_perm;
	*/
}

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
	ft_printf("%*u", widths->link_col + 1, node->lstat.st_nlink);
	ft_printf(" %-*s", (int)ft_strlen(pw->pw_name) + 2, pw->pw_name);
	ft_printf("%s", grp->gr_name);
	ft_printf("%*d ", widths->size_col + 2, node->lstat.st_size);
	print_time(node);
	if (readlink(node->path, link_buf, 1024) > 0)
		ft_printf("%s -> %s\n", node->path, link_buf);//ft_printf("%s -> %s\n", node->file_name, link_buf);
	else if (!(widths->is_file))
		ft_printf("%s\n", node->file_name);
	else
		ft_printf("%s\n", node->path);
	print_extended_attributes(node, widths->flags);
	if (dir_paths && node->type & DT_DIR && ft_strcmp(name, ".") != 0 && ft_strcmp(name, "..") != 0)
		dir_paths[(*i)++] = node->path;
}

/*	ENONENT = No such file or dir
	ENOTDIR = Exists, but not a dir */
int open_directory(char *path, DIR **dst)
{
	char *error;
	char *tmp;
	struct stat tmp_stat;

	*dst = opendir(path);
	if ((!*dst && errno == ENOTDIR) || (!*dst && ft_strcmp(path, ".") != 0 
		&& ft_strcmp(path, "..") != 0 && lstat(path, &tmp_stat) == 0 && errno != EACCES))
	{
		*dst = NULL; 
		errno = 0;
		return (-1);
	}
	if (!*dst && errno != ENOENT && errno != ENAMETOOLONG && errno != EACCES)
	{
		error_exit();
	}
	else if(!*dst)
	{
		error = strerror(errno);
		tmp = ft_strrchr(path, '/');
		//Using write here is it allowed?
		/* This ENOENT thing is here just for moulitest, delete maybe*/
		if (errno != ENOENT)
			write(STDERR_FILENO, "ft_ls: ", 7);
		else
			write(STDERR_FILENO, "ls: ", 4);
		if (!tmp || errno == ENOENT)
			write(STDERR_FILENO, path, ft_strlen(path));
		else
			write(STDERR_FILENO, tmp + 1, ft_strlen(tmp + 1));
		write(STDERR_FILENO, ": ", 2);
		write(STDERR_FILENO, error, ft_strlen(error));
		write(STDERR_FILENO, "\n", 1);
		errno = 0;
		return (0);
	}
	return (1);
}

int main(int argc, char **argv)
{
	t_width		widths_and_flags;
	int i;
	t_file_node *head;
	t_paths		paths;

	i = 0;
	ft_bzero((void *)&paths, sizeof(t_paths));
	ft_bzero((void *)&widths_and_flags, sizeof(widths_and_flags));
	//TODO Free all this shit, THESE DOESTN WRITE NULL AT SCHOOL
	paths.open_dir = (DIR **)ft_memalloc(sizeof(DIR *) * argc + 1);
	paths.arg_paths = (char **)ft_memalloc(sizeof(char *) * argc + 1);
	paths.arg_paths[argc] = NULL;
	paths.open_dir[argc] = NULL;
	i = ls_get_flags(argc, argv, &widths_and_flags.flags);
	sort_arguments(argc - i, &argv[i], &widths_and_flags, paths);
	while (*paths.arg_paths != NULL)
	{
		errno = 0;
		head = create_list(*paths.open_dir, *paths.arg_paths, &widths_and_flags);
		paths.dir_paths = (char **)ft_memalloc(sizeof(char *) * widths_and_flags.dir_amount + 1);
		paths.dir_paths[widths_and_flags.dir_amount] = NULL;
		if (head && widths_and_flags.flags & RECURSIVE)
		{
			choose_output_format(head, &widths_and_flags, paths.dir_paths);
			recursive_traverse(paths.dir_paths, i, &widths_and_flags);
		}	
		else
		{
			if (*(paths.arg_paths + 1) != NULL)
				widths_and_flags.flags |= PRINT_DIR_NAME;
			choose_output_format(head, &widths_and_flags, paths.dir_paths);
		}
//		free_lst(head);
	//	widths_and_flags.flags |= PRINT_DIR_NAME;
		++paths.arg_paths;
		++paths.open_dir;
	//	closedir(*paths.open_dir);
//		free(*paths.arg_paths);
		if (*paths.arg_paths != NULL)
			ft_printf("\n");
	}
	/* Free paths.arg_paths and open_dir */
	return (0);
}