/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_arguments.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 12:49:40 by jniemine          #+#    #+#             */
/*   Updated: 2022/08/07 20:34:46 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

void seperate_name_and_path(char *arg_names, char *filename, char *root_path)
{
	char *slash;
	
	slash = ft_strrchr(arg_names, '/');
	if (!slash)
	{
		ft_strcpy(filename, arg_names);
		ft_strcpy(root_path, ".");
	}
	else
	{
//		ft_strcpy(root_path, "./");
		ft_strcat(filename, slash + 1);
		ft_strncat(root_path, arg_names, ft_strlen(arg_names) - ft_strlen(slash));
	}
}

/* It has already been confirmed that filename exist at path */
t_dir *search_file_pointer(char *path, char *filename)
{
	DIR		*dirp;
	t_dir	*filep;

	filep = NULL;
	dirp = NULL;
	if (open_directory(path, &dirp) == 1)
		filep = read_stream(dirp);
	else
		error_exit();
	while (filep)
	{
		if (ft_strcmp(filep->d_name, filename) == 0)
			return (filep);
		filep = read_stream(dirp);
	}
	return (filep);
}

void free_everything(char **root_paths, t_file_node *head)
{
	int i;
	
	i= 0;
	free_lst(head);
	while(root_paths[i])
		free(root_paths[i++]);
}

/* Remember to free filepointers */
void create_file_list(t_dir **filepointers, t_width *widths, char **root_paths)
{
	t_file_node *head;
	t_file_node *lst_start;
	t_dir		*filep;

	head = create_node();
	lst_start = head;
	while(*filepointers)
	{
		filep = *filepointers;
		get_t_dir_info(filep, head);
		handle_path(*root_paths++, head, filep);
		get_stat_info(head);
		head->type = filep->d_type;
		update_widths(head, widths);
		widths->is_file = 1;
		if (*(++filepointers))
		{
			head->next = create_node();
			head = head->next;
		}
	}
	lst_start = sort(&lst_start, widths->flags, widths);
	lst_start->is_head = 0;
	if (widths->flags & LONG_LST)
		print_loop(lst_start, *widths, NULL);
	else
		print_columns(lst_start, widths, NULL);
	/* Close DIR, free root_paths */
	free_everything(root_paths, lst_start);
}

/* file_names are pointers to program arguments so they dont need freeing */
void create_filepointer(char **file_names, int k, t_width *widths)
{
	char filename[1024];
	char path[1024];
	char **root_paths;
	t_dir **filepointers;
	int i;

	filepointers = (t_dir **)ft_memalloc(sizeof(*filepointers) * k + 1);
	root_paths = (char **)ft_memalloc(sizeof(*root_paths) * k + 1);
	i = 0;
	while(file_names[i] && i < k)
	{
		ft_bzero(path, 1024);
		ft_bzero(filename, 1024);
		seperate_name_and_path(file_names[i], filename, path);
		root_paths[i] = (char *)ft_memalloc(ft_strlen(path) + 1);
		ft_strcpy(root_paths[i], path);
		filepointers[i++] = search_file_pointer(path, filename);
	}
	free(file_names);
	create_file_list(filepointers, widths, root_paths);
}

/* 	Open all arguments, put them in array.
	Sort array with files first and directories last.
	Everything in lexicographical order */

void sort_arguments(int argc, char **argv, t_width *widths, t_paths paths)
{
	int		i;
	int		j;
	int		k;
	char	**file_names;
	DIR		*dirp;
	
	i = 0;
	j = 0;
	k = 0;
	if (!*argv && open_directory(".", paths.open_dir) == 1)
	{
		*paths.arg_paths = ".";
		return ;
	}
	file_names = (char **)ft_memalloc(sizeof(*file_names) * argc);
	while (i < argc)
	{
		dirp = NULL;
		if (open_directory(argv[i], &dirp) == 1)
		{
			paths.arg_paths[j] = argv[i];
			paths.open_dir[j++] = dirp;
		}
		if (!dirp)
			file_names[k++] = argv[i];
		++i;
	}
	if (*file_names)
		create_filepointer(file_names, k, widths);
}