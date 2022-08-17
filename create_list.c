/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 14:44:27 by jniemine          #+#    #+#             */
/*   Updated: 2022/08/17 13:04:34 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

extern int errno;

t_file_node *create_node(void)
{
	t_file_node *new;

	new = (t_file_node *)ft_memalloc(sizeof(t_file_node));
	if (!new)
		error_exit();
	new->is_head = 0;
	new->total_blocks = 0;
	new->path = NULL;
	new->next = NULL;
	return (new);
}

void free_lst(t_file_node *head)
{
	t_file_node *previous;

	while (head)
	{
		previous = head;
		head = head->next;
		free(previous->file_name);
		free(previous->path);
		free(previous);
	}
}

void print_loop(t_file_node *head, t_width widths, char **dir_paths)
{
	int			i;

	i = 0;
//	if (head)
//		ft_printf("\n%s:\n", head->dir_path);
	while (head)
	{
		while (head && !(widths.flags & ALL) && head->file_name[0] == '.')
			head = head->next;
		if (!head)
			break;
		print_stat(head, &widths, dir_paths, &i);
		head = head->next;
	}
	return ;
}
//Create local list, fill it with directory names.
//While there are names in dir list, read list.
//If list empty, return.
//Count number of directories in create_list and create list of directories in print

void debugger(char **paths)
{
	int i;
	
	i = 0;
	while (paths[i])
		printf("%s\n", paths[i++]);
}

void recursive_traverse(char **paths, int i, t_width *widths_flags)
{
	char		**dir_paths;
	t_file_node	*head;
	t_width		widths;
	DIR			*dirp;
	int			ret;

	dirp = NULL;
	head = NULL;
	errno = 0;
	ft_bzero((void *)&widths, sizeof(t_width));
	widths.flags = widths_flags->flags;
	if (paths == NULL || *paths == NULL)
		return ;
	if (!ft_strncmp(*paths, "/", 1))
		ft_printf("\n%s\n", *paths);
	else
		ft_printf("%s%s:\n", "\n./", *paths);
	ret = open_directory(*paths, &dirp);
	if (ret < 0)
		error_exit();
	else if (ret == 0)
		recursive_traverse(++paths, ++i, &widths); //Does this work?
	head = create_list(dirp, *paths, &widths);
	/* This checked for empty head earlier, but now empty head is returned if there is only hidden files which are skipped */
	if (!widths.dir_path || (!head && !dirp))
		return ;
//	widths.flags |= PRINT_DIR_NAME;
	dir_paths = (char **)ft_memalloc(sizeof(char *) * (widths.dir_amount + 1));
	if (!dir_paths || closedir(dirp) < 0)
		error_exit();
	dir_paths[widths.dir_amount] = NULL;
	//TODO: Printer function to choose betweeen long and column
//	print_loop(head, widths, dir_paths);
	choose_output_format(head, &widths, dir_paths);
	if (dir_paths != NULL && *dir_paths != NULL)
		recursive_traverse(dir_paths++, ++i, &widths);
	if (paths != NULL && *paths != NULL)	
		recursive_traverse(++paths, ++i, &widths);
	free_lst(head);
	//TODO: Widths are not universal. Every list needs its own widths.
	//TOTHINK: Should i do the whole linked list before printing?
	//TODO: check print_stats TODO.
}

void handle_path(char *root_path, t_file_node *head, t_dir *dirp, int flags)
{
	int len;

	len = ft_strlen(root_path) + ft_strlen(dirp->d_name) + 2; //+2 for null and ?slash?
	head->path = ft_memalloc(len);
	head->dir_path = ft_memalloc(ft_strlen(root_path) + 1);
	if (!head->path || !head->dir_path)
		error_exit();
	ft_strcpy(head->dir_path, root_path);
	if ((flags & RECURSIVE || flags & ONE_COLUMN) && ft_strncmp(root_path, "./", 2) == 0)
		root_path += 2;
	if (ft_strcmp(root_path, ".") != 0)
		ft_strcat(head->path, root_path);
	if (ft_strlen(head->path) > 0 && head->path[ft_strlen(head->path) - 1] != '/')
		ft_strcat(head->path, "/");
	ft_strcat(head->path, dirp->d_name);
}

void get_t_dir_info(t_dir *filep, t_file_node *node)
{
	if (!filep)
		return ;
	node->dp = *filep;
	node->file_name = (char *)ft_memalloc(sizeof(char) * filep->d_namlen + 1);
	if (!node->file_name)
		error_exit();
	ft_strcpy(node->file_name, filep->d_name);
}

/* Changed this to use only lstat */
void get_stat_info(t_file_node *node)
{
	if (lstat(node->path, &node->stat) < 0 || lstat(node->path, &node->lstat) < 0)
		error_exit();
}

/* readdir returns NULL when end has been reached or on ERROR, make error handling */
t_dir *read_stream(DIR *dirp)
{
	t_dir *filep;

	filep = NULL;
	if (dirp)
		filep = readdir(dirp);	
	if (!filep && errno > 0)
		error_exit();
	return (filep);
}

void update_widths(t_file_node *head, t_width *widths)
{
	++widths->file_amount;
	if (head->type & DT_DIR)
		widths->dir_amount++;
	if (widths->longest_filename < ft_strlen(head->file_name))
		widths->longest_filename = ft_strlen(head->file_name);
	if (widths->link_col < nb_len(head->lstat.st_nlink))	
		widths->link_col = nb_len(head->lstat.st_nlink);
	if (widths->size_col < nb_len(head->lstat.st_size))	
		widths->size_col = nb_len(head->lstat.st_size);
	widths->total_size += head->stat.st_blocks;
	widths->dir_path = ft_memalloc(ft_strlen(head->dir_path) + 1);
	if (!widths->dir_path)
		error_exit();
	ft_strcpy(widths->dir_path, head->dir_path);
}

int wind_over_hidden(DIR *dirp, t_dir **filep, int flags)
{
	if (!(flags & ALL))
	{
		while (*filep && (*filep)->d_name[0] == '.')
			*filep = read_stream(dirp);
	}
	if (!*filep)
		return (1);
	return (0);
}
//Arguments are opened directory and path name to that directory
/* This reads files from one directory at a time */
t_file_node *create_list(DIR *dirp, char *path, t_width *widths)
{
	t_dir		*filep;
	t_file_node	*head;
	t_file_node	*lst_start;
	int			flags;

	flags = widths->flags;
	ft_bzero((void *)widths, sizeof(*widths));
	widths->flags = flags;
	filep = read_stream(dirp);
	if (!filep)
		return (NULL);
	head = create_node();
	lst_start = head;
	while (filep != NULL && dirp != NULL)
	{
		if (wind_over_hidden(dirp, &filep, widths->flags))
		{
	//		head->file_name = path;
	//		head->dir_path = path;
			widths->dir_path = ft_memalloc(ft_strlen(path) + 1);
			ft_strcpy(widths->dir_path, path);
			return (NULL);
		}
		get_t_dir_info(filep, head);
		handle_path(path, head, filep, widths->flags);
		get_stat_info(head);
		head->type = filep->d_type;
		update_widths(head, widths);
		///Do i need to free the list if it fails?
		filep = read_stream(dirp);
		if (filep != NULL)
		{
			head->next = create_node();
			head = head->next;
		}
	}
	if (!filep && errno != 0)
		error_exit();
	return (sort(&lst_start, widths->flags, widths));
}