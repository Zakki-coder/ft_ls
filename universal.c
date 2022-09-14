/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   universal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 20:28:46 by jniemine          #+#    #+#             */
/*   Updated: 2022/09/14 20:28:26 by jniemine         ###   ########.fr       */
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

/* readdir returns NULL when end has been reached
	or on ERROR, make error handling */
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
