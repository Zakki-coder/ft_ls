/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   universal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 20:28:46 by jniemine          #+#    #+#             */
/*   Updated: 2022/09/14 23:58:58 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

void	error_exit(void)
{
	char	*error;

	error = strerror(errno);
	write(STDERR_FILENO, error, ft_strlen(error));
	write(STDERR_FILENO, "\n", 1);
	exit (-1);
}

unsigned int	nb_len(long long nb)
{
	int	len;

	len = 1;
	while (nb >= 10)
	{
		++len;
		nb /= 10;
	}
	return (len);
}

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

t_dir	*read_stream(DIR *dirp)
{
	t_dir	*filep;

	filep = NULL;
	if (dirp)
		filep = readdir(dirp);
	if (!filep && errno > 0)
		error_exit();
	return (filep);
}

t_file_node	*create_node(void)
{
	t_file_node	*new;

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
