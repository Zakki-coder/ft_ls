/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 17:59:01 by jniemine          #+#    #+#             */
/*   Updated: 2022/09/15 17:12:16 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

static void	close_and_free_paths(t_paths paths)
{
	char	**start_arg;
	char	**start_dir;

	start_arg = paths.arg_paths;
	start_dir = paths.dir_paths;
	while (paths.arg_paths && *paths.arg_paths)
	{
		if (paths.open_dir && *paths.open_dir)
		{
			if (closedir(*paths.open_dir) < 0)
				error_exit();
			++(paths.open_dir);
		}
		if (paths.dir_paths && *paths.dir_paths)
		{
			free(*paths.dir_paths);
			++(paths.dir_paths);
		}
		free((*paths.arg_paths));
		++(paths.arg_paths);
	}
	free(start_dir);
	free(start_arg);
}

static void	loop_paths_and_print(t_width *widths, int i, t_paths paths)
{
	t_file_node	*head;

	while (*paths.arg_paths != NULL && *paths.open_dir != NULL)
	{
		errno = 0;
		head = create_list(*paths.open_dir, *paths.arg_paths, widths);
		paths.dir_paths = ft_memalloc(sizeof(char *)
				* (widths->dir_amount + 1));
		if (head && widths->flags & RECURSIVE)
		{
			choose_output_format(head, widths, paths.dir_paths);
			recursive_traverse(paths.dir_paths, i, widths);
		}	
		else
		{
			if (*(paths.arg_paths + 1) != NULL)
				widths->flags |= PRINT_DIR_NAME;
			choose_output_format(head, widths, paths.dir_paths);
		}
		free_lst(head);
		++paths.arg_paths;
		++paths.open_dir;
		if (*paths.arg_paths != NULL)
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
	close_and_free_paths(paths);
	return (0);
}
