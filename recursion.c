/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recursion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 17:56:23 by jniemine          #+#    #+#             */
/*   Updated: 2022/09/22 18:38:23 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

void	free_lst(t_file_node *head)
{
	t_file_node	*previous;

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

static int	check_path(char ***paths, DIR **dirp, int *i, t_width *widths)
{
	int	ret;

	if ((*paths) == NULL || (**paths) == NULL)
		return (-1);
	if (!ft_strncmp(**paths, "/", 1))
		ft_printf("\n%s:\n", **paths);
	else
		ft_printf("%s%s:\n", "\n./", **paths);
	ret = open_directory(**paths, dirp, widths);
	if (ret < 0)
		error_exit();
	else if (ret == 0)
	{
		recursive_traverse(++(*paths), ++(*i), widths);
	}
	return (1);
}

void	recursive_traverse(char **paths, int i, t_width *widths_flags)
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
	if (check_path(&paths, &dirp, &i, &widths) < 0 || *paths == NULL)
		return ;
	head = create_list(dirp, *paths, &widths);
	/* If head is outcommented, then segfault, if not then leak, make better */
	if (/*head &&*/ paths && *paths)
		free(*paths);
	dir_paths = (char **)ft_memalloc(sizeof(char *) * (widths.dir_amount + 1));
	if (!dir_paths || (dirp && closedir(dirp) < 0))
		error_exit();
	dir_paths[widths.dir_amount] = NULL;
	choose_output_format(head, &widths, dir_paths);
	free(widths.dir_path);
	if (dir_paths != NULL && *dir_paths != NULL)
		recursive_traverse(dir_paths, ++i, &widths);
	free(dir_paths);
	if (paths != NULL && *paths != NULL)
		recursive_traverse(paths + 1, ++i, &widths);
}
