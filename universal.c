/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   universal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 20:28:46 by jniemine          #+#    #+#             */
/*   Updated: 2022/09/22 15:31:01 by jniemine         ###   ########.fr       */
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

/* readdir returns NULL when end has been reached
	or on ERROR, make error handling */
int	read_stream(DIR *dirp, t_dir **filep)
{
	if (dirp)
		*filep = readdir(dirp);
	if (!(*filep) && errno > 0)
		error_exit();
	return (1);
}

void	free_node(t_file_node **head)
{
	free((*head)->usr);
	free((*head)->grp);
	free((*head)->ext_attr);
	free((*head)->dir_path);
	free((*head)->file_name);
	free((*head)->path);
//	free(head);
}
