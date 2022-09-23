/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   universal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 20:28:46 by jniemine          #+#    #+#             */
/*   Updated: 2022/09/23 14:05:50 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

void	hex_print(t_file_node *h)
{
	const char			*num = "0123456789abcdef";
	char				hex[11];
	int					i;
	unsigned long long	nb;

	i = 9;
	ft_memset(hex, '0', 11);
	hex[10] = '\0';
	hex[0] = '0';
	hex[1] = 'x';
	nb = h->d_minor;
	while (i > 2)
	{
		hex[i] = num[nb % 16];
		nb /= 16;
		--i;
	}
	ft_printf("  %d, %s ", h->d_major, hex);
}

void	error_exit(void)
{
	char	*error;

	error = strerror(errno);
	write(STDERR_FILENO, error, ft_strlen(error));
	write(STDERR_FILENO, "\n", 1);
	exit (1);
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
}
