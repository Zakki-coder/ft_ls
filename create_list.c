/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 14:44:27 by jniemine          #+#    #+#             */
/*   Updated: 2022/06/27 17:25:53 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

extern int errno;

t_file_node *create_node(void)
{
	t_file_node *new;

	new = (t_file_node *)ft_memalloc(sizeof(t_file_node *));
	if (!new)
		exit(-1); //Set errno
	new->total_blocks = 0;
	new->path = NULL;
	new->next = NULL;
	return (new);
}

//Create local list, fill it with directory names.
//While there are names in dir list, read list.
//If list empty, return.
void recursive_traverse(char **paths)
{
	char *dir_path;
	t_file_node *head;

	dir_path = NULL; //Just for compiler error while testing
	head = create_list(opendir(*paths), dir_path);
	if (*paths == NULL)
		return ;

}

void handle_path(char *root_path, char **dest_path, t_dir *dirp)
{
	int len;

	len = ft_strlen(root_path) + ft_strlen(dirp->d_name) + 2; //+2 for null and ?slash?
	*dest_path = ft_memalloc(len);
	ft_strcat(*dest_path, root_path);
	ft_strcat(*dest_path, "/");
	if (ft_strcmp(dirp->d_name, ".") != 0 && ft_strcmp(dirp->d_name, "..") != 0)
		ft_strcat(*dest_path, dirp->d_name);
}

//Arguments are opened directory and path name to that directory
t_file_node *create_list(DIR *dirp, char *path)
{
	t_dir *filep;
	t_file_node *head;
	t_file_node *lst_start;

	//TODO: read stats also
	head = create_node();
	filep = readdir(dirp);
	lst_start = head;
	while (filep)
	{
		ft_memcpy((void *)&head->dp, (void *)filep,  sizeof(head->dp));
		handle_path(path, &head->path, filep);
		if (stat(head->path, &head->stat) < 0 || lstat(head->path, &head->lstat) < 0)
			exit(-1); //Do some errno stuff here.
		head->next = create_node();
		//Do i need to free the list if it fails?
		head = head->next;
		filep = readdir(dirp);
	}
	return (lst_start);
}