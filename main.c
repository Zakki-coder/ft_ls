/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 17:59:01 by jniemine          #+#    #+#             */
/*   Updated: 2022/09/22 18:46:08 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

static void	close_and_free_paths(t_paths paths)
{
	char **start_arg = paths.arg_paths;
	DIR **start_open = paths.open_dir;

	while(paths.open_dir && *paths.open_dir)
	{
		if (closedir(*paths.open_dir) < 0)
			error_exit();
		++(paths.open_dir);
	}
	while (paths.arg_paths && *paths.arg_paths)
	{
		free((*paths.arg_paths));
		++(paths.arg_paths);
	}
//	if (start_arg && *start_arg)
		free(start_arg);
//	if (start_open && *start_open)
		free(start_open);
}

static void	free_dpath(t_paths paths)
{
	while(paths.dir_paths && *paths.dir_paths)
	{
		free(*paths.dir_paths);
		++paths.dir_paths;
	}
}

static void not_recursive(t_paths paths, t_width *widths, t_file_node *head, int j)
{
	if ((paths.arg_paths[j + 1]) != NULL)
		widths->flags |= PRINT_DIR_NAME;
	choose_output_format(head, widths, paths.dir_paths);
	free_dpath(paths);
}

static void	loop_paths_and_print(t_width *widths, int i, t_paths paths)
{
	t_file_node	*head;
	int 		j;

	j = 0;
	while (paths.arg_paths[j] != NULL && paths.open_dir[j] != NULL)
	{
		errno = 0;
		head = create_list(paths.open_dir[j], paths.arg_paths[j], widths);
		paths.dir_paths = ft_memalloc(sizeof(char *)
				* (widths->dir_amount + 1));
		if (head && widths->flags & RECURSIVE)
		{
			choose_output_format(head, widths, paths.dir_paths);
			recursive_traverse(paths.dir_paths, i, widths);
		}	
		else
		{
			not_recursive(paths, widths, head, j);
			// if ((paths.arg_paths[j + 1]) != NULL)
			// 	widths->flags |= PRINT_DIR_NAME;
			// choose_output_format(head, widths, paths.dir_paths);
			// free_dpath(paths);
		}
		free(paths.dir_paths);
		++j;
		if (paths.arg_paths[j] != NULL)
			ft_printf("\n");
	}
}

int	main(int argc, char **argv)
{
	t_width		widths_and_flags;
	int			i;
	t_paths		paths;

	i = 0;
	ft_bzero((void *)&paths, sizeof(t_paths));
	ft_bzero((void *)&widths_and_flags, sizeof(widths_and_flags));
	paths.open_dir = (DIR **)ft_memalloc(sizeof(DIR *) * (argc + 1));
	paths.arg_paths = (char **)ft_memalloc(sizeof(char *) * (argc + 1));
	i = ls_get_flags(argc, argv, &widths_and_flags.flags);
	sort_arguments(argc - i, &argv[i], &widths_and_flags, paths);
	loop_paths_and_print(&widths_and_flags, i, paths);
	free(widths_and_flags.dir_path);
	close_and_free_paths(paths);
	return (0);
}
