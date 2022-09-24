/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_arguments.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 12:49:40 by jniemine          #+#    #+#             */
/*   Updated: 2022/09/24 16:54:18 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

static char	**sort_argv(char **argv)
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

static void	sepertate_dir_and_file(char **argv, t_paths *paths,
	t_width *widths, char **file_names)
{
	int	open_dir_ret;
	DIR	*dirp;

	dirp = NULL;
	open_dir_ret = open_directory(*argv, &dirp, widths);
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
		if (open_dir_ret == -2)
			widths->is_file = 1;
	}
	if (open_dir_ret == 0)
		widths->flags |= PRINT_DIR_NAME;
}

/* 	Open all arguments, put them in array.
	Sort array with files first and directories last.
	Everything in lexicographical order */
void	sort_arguments(int argc, char **argv, t_width *widths, t_paths paths)
{
	char	**file_names;

	if (!*argv && open_directory(".", paths.open_dir, NULL) == 1)
	{
		*paths.arg_paths = ft_strdup(".");
		return ;
	}
	argv = sort_argv(argv);
	file_names = (char **)ft_memalloc(sizeof(*file_names) * (argc + 1));
	if (!file_names)
		error_exit();
	while (*argv != NULL)
	{
		sepertate_dir_and_file(argv, &paths, widths, file_names);
		++argv;
	}
	if (paths.j > 1)
		widths->flags |= PRINT_DIR_NAME;
	if (*paths.arg_paths && *file_names)
		widths->flags |= PRINT_NL;
	if (*file_names)
		create_filepointer(file_names, paths.i, widths);
	free(file_names);
}
