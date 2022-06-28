/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 14:44:27 by jniemine          #+#    #+#             */
/*   Updated: 2022/06/28 20:21:41 by jniemine         ###   ########.fr       */
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
	new->dp = (t_dir *)malloc(sizeof(t_dir));
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
	if (ft_strcmp(dirp->d_name, ".") != 0 && ft_strcmp(dirp->d_name, "..") != 0)
	{
		ft_strcat(*dest_path, "/");
		ft_strcat(*dest_path, dirp->d_name);
	}
}

void get_t_dir_info(t_dir *filep, t_file_node *node)
{
	node->type = filep->d_type;
	node->namelen = filep->d_namlen;
	if (ft_strcmp(filep->d_name, ".") == 0 )
	{
		node->file_name = (char *)ft_memalloc(sizeof(char) * 2);
		node->file_name[0] = '.';
		ft_printf("NAAAME:%s\n", node->file_name);
	}
	else if (ft_strcmp(filep->d_name, "..") == 0)
	{
		node->file_name = ft_memalloc(2 + 1);
		ft_strcpy(node->file_name, "..");
	}
	else
	{
		node->file_name = ft_memalloc(filep->d_namlen + 1);
		ft_strcpy(node->file_name, filep->d_name);
	}
	printf("name: %s\n", node->file_name);
	printf("name: %s\n",filep->d_name);
}

void get_stat_info(t_file_node *node)
{
	t_stat statp;

	stat(node->path, &statp);
	node->st_uid = statp.st_uid;
	node->st_blocks = statp.st_blocks;
	node->st_mode = statp.st_mode;
	node->st_nlink = statp.st_nlink;
	node->st_gid = statp.st_nlink;
	node->st_gid = statp.st_gid;
	node->tv_sec = statp.st_mtimespec.tv_sec;
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
		get_t_dir_info(filep, head);
		handle_path(path, &head->path, filep);
		get_stat_info(head);
	//	if (lstat(head->path, &head->stat) < 0)
	//	{
	//		printf("%s\n", strerror(errno));
	//		exit(-1); //Do some errno stuff here.
	//	}
		print_stat(head);
		head->next = create_node();
		//Do i need to free the list if it fails?
		head = head->next;
		filep = readdir(dirp);
	}
	return (lst_start);
}