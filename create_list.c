/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 14:44:27 by jniemine          #+#    #+#             */
/*   Updated: 2022/07/07 15:20:31 by jniemine         ###   ########.fr       */
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

void print_loop(t_file_node *head, t_width widths, char **dir_paths)
{
	int i;

	i = 0;
	while (head)
	{
		//Why is it that we have local copy of widths and we are passing its addres?
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

	printf("Dirpath: %s, %d\n", *paths, i);
	ft_bzero((void *)&widths, sizeof(t_width));
	widths = *widths_flags;
	if (!paths || *paths == NULL)
		return ;
	dirp = open_directory(*paths);
	if (!dirp && errno == ENOENT)
		recursive_traverse(++paths, ++i, &widths);
	if (!dirp)
		error_exit();
	head = create_list(dirp, *paths, &widths);
	dir_paths = (char **)ft_memalloc(sizeof(char *) * widths.dir_amount + 1);
//	dir_paths[widths.dir_amount] = NULL;
	if (!dir_paths)
		error_exit();
	print_loop(head, widths, dir_paths);
	if (*dir_paths)
		recursive_traverse(dir_paths++, ++i, &widths);
/*	while (*dir_paths)
	{
//		printf("First loop: %d\n", i);
//		debugger(dir_paths);
		recursive_traverse(dir_paths++, ++i, &widths);
	}
	*/
	if ((*paths))	
	{
//		printf("Second loop: %d\n", i);
	//	debugger(paths);
		recursive_traverse(++paths, ++i, &widths);
	}
	//TODO: Widths are not universal. Every list needs its own widths.
	//TOTHINK: Should i do the whole linked list before printing?
	//TODO: check print_stats TODO.
}


void handle_path(char *root_path, char **dest_path, t_dir *dirp)
{
	int len;

	len = ft_strlen(root_path) + ft_strlen(dirp->d_name) + 2; //+2 for null and ?slash?
	*dest_path = ft_memalloc(len);
	if (!*dest_path)
		error_exit();
	ft_strcat(*dest_path, root_path);
	if (ft_strcmp(dirp->d_name, ".") != 0 && ft_strcmp(dirp->d_name, "..") != 0)
	{
		ft_strcat(*dest_path, "/");
		ft_strcat(*dest_path, dirp->d_name);
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


//Arguments are opened directory and path name to that directory
t_file_node *create_list(DIR *dirp, char *path, t_width *widths)
{
	t_dir *filep;
	t_file_node *head;
	t_file_node *lst_start;
	unsigned int largest[2];

	ft_memset(largest, 0, sizeof(largest));
	head = create_node();
	head->is_head = 1;
	filep = readdir(dirp);
	lst_start = head;
	while (filep)
	{
		get_t_dir_info(filep, head);
		handle_path(path, &head->path, filep);
		get_stat_info(head);
		if (filep->d_type & DT_DIR)
			widths->dir_amount++;
		head->type = filep->d_type;
		if (widths->link_col < nb_len(head->stat.st_nlink))	
			widths->link_col = nb_len(head->stat.st_nlink);
		if (widths->size_col < nb_len(head->stat.st_size))	
			widths->size_col = nb_len(head->stat.st_size);
		widths->total_size += head->stat.st_blocks;
		//Do i need to free the list if it fails?
		filep = readdir(dirp);
		if (filep)
		{
			head->next = create_node();
			head = head->next;
		}
	}
	return (lst_start);
}