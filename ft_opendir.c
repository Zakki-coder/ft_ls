/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_opendir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 17:59:01 by jniemine          #+#    #+#             */
/*   Updated: 2022/09/11 18:42:44 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

/* Using write here */
/*
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
*/


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
	timep += 4;
	ft_strncat(output, timep, 3);
	timep += 3;
	time_difference = current_time - node->stat.st_mtimespec.tv_sec;
	over_six_months(output, timep, time_difference);
	ft_printf("%-*s", ft_strlen(output) + 1, output);
}

/*
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
*/

void parse_acl(char *acl, int i)
{
	char buf[256];

	ft_bzero(buf, 256);
	acl += ft_strchr(acl, '\n') + 1 - acl;
	ft_strncpy(buf, acl, ft_strchr(acl, ':') - acl + 1);	
	acl = ft_strchr(ft_strchr(acl, ':') + 1, ':') + 1;
	ft_strncat(buf, acl, ft_strchr(acl, ':') - acl);
	acl = ft_strchr(ft_strchr(acl, ':') + 1, ':') + 1;
	ft_strcat(buf, " ");
	ft_strncat(buf, acl, ft_strchr(acl, ':') - acl);
	acl = ft_strchr(acl, ':') + 1;
	ft_printf(" %d: %s\n", i, buf);
}

void print_extended_attributes(t_file_node *head, int flags)
{
	int			i;
	int			k;
	int			tab_n;
	int			print_len;
//	acl_entry_t	entryp;
//	acl_permset_t permsetp;
//	acl_tag_t	*tag_type;
	ssize_t		len;
	char		*ret;

	i = 0;
	/* Maybe you already have the lengths saved in struct */
//	tag_type = ft_memalloc(sizeof(*tag_type));
	if(flags & EXT_ATTR && head->ext_attr != NULL)
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
		len = 1;
		k = 0;
		i = 0;
	//	if (acl_get_entry(head->acl, ACL_FIRST_ENTRY, &entryp) < 0)
	//		error_exit();
		while(k < len) 
		{
		//	if(acl_get_permset(entryp, &permsetp) < 0)
		//		error_exit();
		//	if(acl_get_tag_type(entryp,	tag_type) < 0)
		//		error_exit();
			ret = acl_to_text(head->acl, &len);
			parse_acl(ret + k, i++);
			k += ft_strlen(ret) + 1;
			//	if(acl_get_entry(head->acl, ++i, &entryp) <= 0)
			//		break ;
		}
	}
}

void print_size_col(t_file_node *node, t_width *widths)
{
	if (node->type == DT_BLK || node->type == DT_CHR)
		ft_printf(" %d, %d ", node->d_major, node->d_minor); 
	else
		ft_printf("%*d ", widths->size_col + 1, node->lstat.st_size);
}

void print_stat(t_file_node *node, t_width *widths, char **dir_paths, int *i)
{
	char			*name;
	char			link_buf[1024];

	ft_bzero((void *)link_buf, 1024);
	name = node->file_name;
	if (node->is_head)
		ft_printf("total %llu\n", widths->total_size);
	print_permissions(node->lstat.st_mode, node);
	ft_printf("%*u ", widths->link_col + 1, node->lstat.st_nlink);
	ft_printf("%-*s", widths->max_usr_col + 2, node->usr);
	ft_printf("%-*s", widths->max_grp_col + 1, node->grp);
	print_size_col(node, widths);
	print_time(node);
	if (readlink(node->path, link_buf, 1024) > 0)
	{
		if (!(widths->is_file))
			ft_printf("%s -> %s\n", node->file_name, link_buf);
		else
			ft_printf("%s -> %s\n", node->path, link_buf);
	}
	else if (!(widths->is_file))
		ft_printf("%s\n", node->file_name);
	else
		ft_printf("%s\n", node->path);
	print_extended_attributes(node, widths->flags);
	if (dir_paths && node->type & DT_DIR && ft_strcmp(name, ".") != 0 && ft_strcmp(name, "..") != 0)
		dir_paths[(*i)++] = node->path;
}


/* This tests if the folder has attribute rootles */
/*
int test_special_case_rootless(char *path)
{
	char	link[1024];

	if (path[ft_strlen(path) - 1] == '/')
		return (0);
	ft_bzero(link, 1024);
	if(readlink(path, link, 1023) > 0)
		return (1);
	return (0);
}
*/
/*	ENONENT = No such file or dir
	ENOTDIR = Exists, but not a dir */


void close_and_free_paths(t_paths paths)
{
	while(paths.arg_paths && *paths.arg_paths)
	{
		if (paths.open_dir && *paths.open_dir)
		{
			if (closedir(*paths.open_dir) < 0)
				error_exit();
			++(paths.open_dir);
		}
		if (paths.dir_paths && *paths.dir_paths)
		{
			free(*paths.dir_paths);
			free(paths.dir_paths);
			++(paths.dir_paths);
		}
		free((*paths.arg_paths));
		free((paths.arg_paths));
		++(paths.arg_paths);
	}
}

void	loop_paths_and_print(t_width *widths, int i, t_paths paths)
{
	t_file_node *head;

	while (*paths.arg_paths != NULL)
	{
		errno = 0;
		head = create_list(*paths.open_dir, *paths.arg_paths, widths);
		paths.dir_paths = (char **)ft_memalloc(sizeof(char *) * widths->dir_amount + 1);
		paths.dir_paths[widths->dir_amount] = NULL;
		if (head && widths->flags & RECURSIVE)
		{
			choose_output_format(head, widths, paths.dir_paths);
			recursive_traverse(paths.dir_paths, i, widths);
		}	
		else
		{
			if (*(paths.arg_paths + 1) != NULL)
				widths->flags |= PRINT_DIR_NAME;
			choose_output_format(head, widths, paths.dir_paths);
		}
		free_lst(head);
		++paths.arg_paths;
		++paths.open_dir;
		if (*paths.arg_paths != NULL)
			ft_printf("\n");
	}
}

int main(int argc, char **argv)
{
	t_width		widths_and_flags;
	int i;
	t_paths		paths;

	i = 0;
	ft_bzero((void *)&paths, sizeof(t_paths));
	ft_bzero((void *)&widths_and_flags, sizeof(widths_and_flags));
	paths.open_dir = (DIR **)ft_memalloc(sizeof(DIR *) * argc + 1);
	paths.arg_paths = (char **)ft_memalloc(sizeof(char *) * argc + 1);
	i = ls_get_flags(argc, argv, &widths_and_flags.flags);
	sort_arguments(argc - i, &argv[i], &widths_and_flags, paths);
	loop_paths_and_print(&widths_and_flags, i, paths);
	close_and_free_paths(paths);
	return (0);
}