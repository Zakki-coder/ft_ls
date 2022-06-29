/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 14:44:27 by jniemine          #+#    #+#             */
/*   Updated: 2022/06/29 16:43:18 by jniemine         ###   ########.fr       */
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

//Create local list, fill it with directory names.
//While there are names in dir list, read list.
//If list empty, return.
/*
void recursive_traverse(char **paths)
{
	char *dir_path;
	t_file_node *head;

	dir_path = NULL; //Just for compiler error while testing
	head = create_list(opendir(*paths), dir_path);
	if (*paths == NULL)
		return ;

}
*/

void handle_path(char *root_path, char **dest_path, t_dir *dirp)
{
	int len;

	len = ft_strlen(root_path) + ft_strlen(dirp->d_name) + 2; //+2 for null and ?slash?
	*dest_path = ft_memalloc(len);
	if (*dest_path)
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

	//TODO: read stats also
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