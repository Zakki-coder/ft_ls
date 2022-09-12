/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_arguments.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 12:49:40 by jniemine          #+#    #+#             */
/*   Updated: 2022/09/12 18:58:09 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

void	seperate_name_and_path(char *arg_names, char *filename, char *root_path)
{
	char	*slash;
	int		n;
	int		len;

	n = 1;
	len = 0;
	slash = ft_strrchr(arg_names, '/');
	if (!slash)
	{
		ft_strcpy(filename, arg_names);
		ft_strcpy(root_path, ".");
	}
	else
	{
		len = ft_strlen(arg_names) - ft_strlen(slash + n);
		ft_strcat(filename, slash + n);
		ft_strncat(root_path, arg_names, len);
	}
}

/* It has already been confirmed that filename exist at path */
t_dir	*search_file_pointer(char *path, char *filename)
{
	DIR		*dirp;
	t_dir	*filep;

	filep = NULL;
	dirp = NULL;
	if (open_directory(path, &dirp) == 1)
		filep = read_stream(dirp);
	while (filep)
	{
		if (ft_strcmp(filep->d_name, filename) == 0)
			return (filep);
		filep = read_stream(dirp);
	}
	return (filep);
}

void	free_everything(char **root_paths, t_file_node *head)
{
	int	i;

	i = 0;
	free_lst(head);
	while (root_paths[i])
		free(root_paths[i++]);
}

static void	print_file_list(t_file_node *lst_start, t_width *widths)
{
	lst_start = sort(&lst_start, widths->flags, widths);
	lst_start->is_head = 0;
	if (widths->flags & LONG_LST)
		print_loop(lst_start, *widths, NULL);
	else
		print_columns(lst_start, widths, NULL);
}

/* Remember to free filepointers */
void	create_file_list(t_dir **fileps, t_width *widths, char **root_paths)
{
	t_file_node	*head;
	t_file_node	*lst_start;
	t_dir		*filep;

	head = create_node();
	lst_start = head;
	while (*fileps != NULL)
	{
		filep = *fileps;
		get_t_dir_info(filep, head);
		handle_path(*root_paths++, head, filep, widths->flags);
		get_stat_info(head);
		head->type = filep->d_type;
		head->flags = widths->flags;
		update_widths(head, widths);
		widths->is_file = 1;
		if (*(++fileps) != NULL)
		{
			head->next = create_node();
			head = head->next;
		}
	}
	print_file_list(lst_start, widths);
	free_everything(root_paths, lst_start);
}

/* file_names are pointers to program arguments so they dont need freeing */
void	create_filepointer(char **file_names, int k, t_width *widths)
{
	char	filename[1024];
	char	path[1024];
	char	**root_paths;
	t_dir	**filepointers;
	int		i;

	filepointers = (t_dir **)ft_memalloc(sizeof(*filepointers) * k + 1);
	root_paths = (char **)ft_memalloc(sizeof(*root_paths) * k + 1);
	filepointers[k] = NULL;
	root_paths[k] = NULL;
	i = 0;
	while (file_names[i] && i < k)
	{
		ft_bzero(path, 1024);
		ft_bzero(filename, 1024);
		seperate_name_and_path(file_names[i], filename, path);
		root_paths[i] = (char *)ft_memalloc(ft_strlen(path) + 1);
		ft_strcpy(root_paths[i], path);
		filepointers[i++] = search_file_pointer(path, filename);
		filepointers[i] = NULL;
	}
	free(file_names);
	create_file_list(filepointers, widths, root_paths);
	widths->flags |= PRINT_DIR_NAME;
}

char	**sort_argv(char **argv)
{
	char	*temp;
	int		swap_flag;
	int		i;

	swap_flag = 1;
	while (swap_flag)
	{
		i = 0;
		swap_flag = 0;
		while (argv[i] != NULL)
		{
			if (argv[i + 1] != NULL && ft_strcmp(argv[i], argv[i + 1]) > 0)
			{
				temp = argv[i];
				argv[i] = argv[i + 1];
				argv[i + 1] = temp;
				swap_flag = 1;
			}
			++i;
		}
	}
	return (&argv[0]);
}

void sepertate_dir_and_file(char **argv, t_paths *paths, t_width *widths, char **file_names)
{
	int	open_dir_ret;
	DIR	*dirp;

	dirp = NULL;
	open_dir_ret = open_directory(*argv, &dirp);
	if (open_dir_ret == 1)
	{
		paths->arg_paths[paths->j] = ft_strdup(*argv);
		paths->open_dir[paths->j++] = dirp;
		paths->arg_paths[paths->j] = NULL;
		paths->open_dir[paths->j] = NULL;
	}
	if (!dirp && (open_dir_ret == -1 || open_dir_ret == -2))
	{
		file_names[paths->i++] = ft_strdup(*argv);
		file_names[paths->i] = NULL;
		if (open_dir_ret == -2)
			widths->is_file = 1;
	}
	if (open_dir_ret == 0)
		widths->flags |= PRINT_DIR_NAME;
}
/* 	Open all arguments, put them in array.
	Sort array with files first and directories last.
	Everything in lexicographical order */
void sort_arguments(int argc, char **argv, t_width *widths, t_paths paths)
{
	int		j;
	int		k;
	int		open_dir_ret;
	char	**file_names;
	DIR		*dirp;

	j = 0;
	k = 0;
	paths.j = 0;
	paths.i = 0;
	open_dir_ret = 0;
	dirp = NULL;
	if (!*argv && open_directory(".", paths.open_dir) == 1)
	{
		*paths.arg_paths = ft_strdup(".");
//		*paths.arg_paths = ".";
		return ;
	}
	argv = sort_argv(argv);
	file_names = (char **)ft_memalloc(sizeof(*file_names) * (argc + 1));
	file_names[argc] = NULL;
	file_names[argc + 1] = NULL;
	if (!file_names)
		error_exit();
	while (*argv != NULL)
	{
		sepertate_dir_and_file(argv, &paths, widths, file_names);
//		open_dir_ret = open_directory(*argv, &dirp);
//		if (open_dir_ret == 1)
//		{
//			paths.arg_paths[j] = ft_strdup(*argv);
//			paths.open_dir[j++] = dirp;
//			paths.arg_paths[j] = NULL;
//			paths.open_dir[j] = NULL;
//		}
//		if (!dirp && (open_dir_ret == -1 || open_dir_ret == -2))
//		{
//			file_names[k++] = ft_strdup(*argv);
//			file_names[k] = NULL;
//			if (open_dir_ret == -2)
//				widths->is_file = 1;
//		}
//		if (open_dir_ret == 0)
//			widths->flags |= PRINT_DIR_NAME;
		++argv;
	}
	if (paths.j > 1)
		widths->flags |= PRINT_DIR_NAME;
	if (*paths.arg_paths && *file_names)
		widths->flags |= PRINT_NL;
	if (*file_names)
		create_filepointer(file_names, paths.i, widths);
}
