/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 14:44:27 by jniemine          #+#    #+#             */
/*   Updated: 2022/08/02 17:06:35 by jniemine         ###   ########.fr       */
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
	if (head)
		ft_printf("\n%s:\n", head->dir_path);
	while (head)
	{
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
	char **dir_paths;
	t_file_node *head;
	t_width widths;
	DIR *dirp;

	ft_bzero((void *)&widths, sizeof(t_width));
	widths.flags = widths_flags->flags;
	if (paths == NULL || *paths == NULL || **paths == '\0')
		return ;
	dirp = open_directory(*paths);
//	if (!dirp && errno == ENOENT)
	//	recursive_traverse(++paths, ++i, &widths); //Does this work?
	if (!dirp)
		error_exit();
	head = create_list(dirp, *paths, &widths);
	dir_paths = (char **)ft_memalloc(sizeof(char *) * (widths.dir_amount + 1));
	if (!dir_paths || closedir(dirp) < 0)
		error_exit();
	//TODO: Printer function to choose betweeen long and column
	print_loop(head, widths, dir_paths);
	if (dir_paths && *dir_paths)
	{
		recursive_traverse(dir_paths++, ++i, &widths);
	}
	if (paths && *paths)	
	{
		recursive_traverse(++paths, ++i, &widths);
	}
	free_lst(head);
	//TODO: Widths are not universal. Every list needs its own widths.
	//TOTHINK: Should i do the whole linked list before printing?
	//TODO: check print_stats TODO.
}

void handle_path(char *root_path, t_file_node *head, t_dir *dirp)
{
	int len;

	len = ft_strlen(root_path) + ft_strlen(dirp->d_name) + 2; //+2 for null and ?slash?
	head->path = ft_memalloc(len);
	head->dir_path = ft_memalloc(ft_strlen(root_path) + 1);
	ft_strcpy(head->dir_path, root_path);
	if (!head->path)
		error_exit();
	ft_strcat(head->path, root_path);
	if (ft_strcmp(dirp->d_name, ".") != 0/* && ft_strcmp(dirp->d_name, "..") != 0*/)
	{
		ft_strcat(head->path, "/");
		ft_strcat(head->path, dirp->d_name);
	}
}

void get_t_dir_info(t_dir *filep, t_file_node *node)
{
	node->dp = *filep;
	node->file_name = (char *)ft_memalloc(sizeof(char) * filep->d_namlen + 1);
	if (!node->file_name)
		error_exit();
	ft_strcpy(node->file_name, filep->d_name);
}

void get_stat_info(t_file_node *node)
{
	if (stat(node->path, &node->stat) < 0 || lstat(node->path, &node->lstat) < 0)
		error_exit();
}

t_dir *read_stream(DIR *dirp, int flags)
{
	t_dir *filep;

	filep = readdir(dirp);	
	while (filep && !(flags & ALL) && filep->d_name[0] == '.')
		filep = readdir(dirp);
	return (filep);
}

void update_widths(t_file_node *head, t_width *widths)
{
	++widths->file_amount;
	if (head->type & DT_DIR)
		widths->dir_amount++;
	if (widths->longest_filename < ft_strlen(head->file_name))
		widths->longest_filename = ft_strlen(head->file_name);
	if (widths->link_col < nb_len(head->stat.st_nlink))	
		widths->link_col = nb_len(head->stat.st_nlink);
	if (widths->size_col < nb_len(head->stat.st_size))	
		widths->size_col = nb_len(head->stat.st_size);
	widths->total_size += head->stat.st_blocks;
}
//Arguments are opened directory and path name to that directory
/* This reads files from one directory at a time */
t_file_node *create_list(DIR *dirp, char *path, t_width *widths)
{
	t_dir *filep;
	t_file_node *head;
	t_file_node *lst_start;

	filep = read_stream(dirp, widths->flags);
	if (!filep)
		return (NULL);
	head = create_node();
//	head->is_head = 1;
	lst_start = head;
	while (filep)
	{
	//	++widths->file_amount;
		get_t_dir_info(filep, head);
		handle_path(path, head, filep);
		get_stat_info(head);
//		if (filep->d_type & DT_DIR)
//			widths->dir_amount++;
		head->type = filep->d_type;
		update_widths(head, widths);
//		if (widths->longest_filename < ft_strlen(head->file_name))
//			widths->longest_filename = ft_strlen(head->file_name);
//		if (widths->link_col < nb_len(head->stat.st_nlink))	
//			widths->link_col = nb_len(head->stat.st_nlink);
//		if (widths->size_col < nb_len(head->stat.st_size))	
//			widths->size_col = nb_len(head->stat.st_size);
//		widths->total_size += head->stat.st_blocks;
		//Do i need to free the list if it fails?
		filep = read_stream(dirp, widths->flags);
		if (filep)
		{
			head->next = create_node();
			head = head->next;
		}
	}
	if (!filep && errno != 0)
		error_exit();
	return (sort(&lst_start, widths->flags));
}