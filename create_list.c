/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 14:44:27 by jniemine          #+#    #+#             */
/*   Updated: 2022/09/12 17:55:02 by jniemine         ###   ########.fr       */
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
	ft_bzero(new, sizeof(*new));
	new->is_head = 0;
	new->total_blocks = 0;
	new->ext_attr = NULL;
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
		free(previous->usr);
		free(previous->grp);
		free(previous->ext_attr);
		free(previous->dir_path);
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

static int check_path(char ***paths, DIR **dirp, int *i, t_width *widths)
{
	int ret;

	if (*paths == NULL || **paths == NULL)
		return (-1);
	if (!ft_strncmp(**paths, "/", 1))
		ft_printf("\n%s:\n", **paths);
	else
		ft_printf("%s%s:\n", "\n./", **paths);
	ret = open_directory(**paths, dirp);
	if (ret < 0)
		error_exit();
	else if (ret == 0)	
		recursive_traverse(++(*paths), ++(*i), widths);
	return (1);
}

void recursive_traverse(char **paths, int i, t_width *widths_flags)
{
	char		**dir_paths;
	t_file_node	*head;
	t_width		widths;
	DIR			*dirp;

	dirp = NULL;
	head = NULL;
	errno = 0;
	ft_bzero((void *)&widths, sizeof(t_width));
	widths.flags = widths_flags->flags;
	if(check_path(&paths, &dirp, &i, &widths) < 0)
		return ;
	head = create_list(dirp, *paths, &widths);
	dir_paths = (char **)ft_memalloc(sizeof(char *) * (widths.dir_amount + 1));
	if (!dir_paths || closedir(dirp) < 0)
		error_exit();
	dir_paths[widths.dir_amount] = NULL;
	choose_output_format(head, &widths, dir_paths);
	if (dir_paths != NULL && *dir_paths != NULL)
		recursive_traverse(dir_paths++, ++i, &widths);
	if (paths != NULL && *paths != NULL)	
		recursive_traverse(++paths, ++i, &widths);
	free_lst(head);
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
	node->file_name = (char *)ft_memalloc(sizeof(char) * filep->d_namlen + 1);
	if (!node->file_name)
		error_exit();
	ft_strcpy(node->file_name, filep->d_name);
}

/* Get user and group info also */
/* Get device minor and major also */
void get_stat_info(t_file_node *node)
{
	struct passwd	*pw;
	struct group	*grp;

	if (lstat(node->path, &node->stat) < 0 || lstat(node->path, &node->lstat) < 0)
		error_exit();
	pw = getpwuid(node->lstat.st_uid);
	grp = getgrgid(node->lstat.st_gid);
	if (!pw || !grp)
		error_exit();
	node->usr = ft_strdup(pw->pw_name);
	node->grp = ft_strdup(grp->gr_name);
	if (!node->usr || !node->grp)
		error_exit();
	node->d_minor = minor(node->stat.st_rdev);
	node->d_major = major(node->stat.st_rdev);
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
	unsigned int len;

	++widths->file_amount;
	if (head->type & DT_DIR)
		widths->dir_amount++;
	len = ft_strlen(head->file_name);
	if (widths->longest_filename < len)
		widths->longest_filename = len;
	/* Really could just compare ints and do nb_len for the biggest later in print */
	if (widths->link_col < nb_len(head->lstat.st_nlink))	
		widths->link_col = nb_len(head->lstat.st_nlink);
	if (widths->size_col < nb_len(head->lstat.st_size))	
		widths->size_col = nb_len(head->lstat.st_size);
	len = ft_strlen(head->usr);
	if (widths->max_usr_col < len)
		widths->max_usr_col = len;
	len = ft_strlen(head->grp);
	if (widths->max_grp_col < len)
		widths->max_grp_col = len;
	widths->total_size += head->stat.st_blocks;
	widths->dir_path = ft_strdup(head->dir_path);
	if (!widths->dir_path)
		error_exit();
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
	t_file_node	*prev;
	t_file_node	*lst_start;
	int			flags;
	int			something_has_been_created;

	something_has_been_created = 0;
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
			if (!something_has_been_created)
			{
				widths->dir_path = ft_memalloc(ft_strlen(path) + 1);
				ft_strcpy(widths->dir_path, path);
				return(NULL);
			}
			free_lst(prev->next);
			prev->next = NULL;
			break ;
		}
		something_has_been_created = 1;
		get_t_dir_info(filep, head);
		handle_path(path, head, filep, widths->flags);
		get_stat_info(head);
		head->type = filep->d_type;
		update_widths(head, widths);
		filep = read_stream(dirp);
		if (filep != NULL)
		{
			head->next = create_node();
			prev = head;
			head = head->next;
		}
	}
	if (!filep && errno != 0)
		error_exit();
	return (sort(&lst_start, widths->flags, widths));
}