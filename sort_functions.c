/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 18:57:24 by jniemine          #+#    #+#             */
/*   Updated: 2022/09/21 23:53:47 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

int	reverse_strcmp(const char *s1, const char *s2)
{
	return (-1 * ft_strcmp(s1, s2));
}

/*
char	*month_rearrange(char *time)
{
	char	month[4];
	char	*new_date;
	char	months[37];
	int		i;

	ft_strcpy(months, "JanFebMarAprMayJunJulAugSepOctNovDec");
	months[36] = '\0';
	new_date = ft_memalloc(ft_strlen(time));
	if (!new_date)
		error_exit();
	ft_bzero(month, 4);
	time += 4;
	ft_strncpy(month, time, 3);
	i = 0;
	while (ft_strncmp(&months[i], month, 3) != 0)
		i += 3;
	time += 16;
	ft_strncpy((void *)new_date, (void *)time, 4);
	ft_strcat(new_date, ft_itoa(i));
	time -= 12;
	ft_strncat(new_date, time, 11);
	return (new_date);
}
*/
int	time_compare(struct stat t1, struct stat t2)
{
	if (t1.st_mtimespec.tv_sec > t2.st_mtimespec.tv_sec)
		return (-1);
	else if (t1.st_mtimespec.tv_sec == t2.st_mtimespec.tv_sec)
	{
		if (t1.st_mtimespec.tv_nsec > t2.st_mtimespec.tv_nsec)
			return (-1);
		else if (t1.st_mtimespec.tv_nsec == t2.st_mtimespec.tv_nsec)
			return (0);
	}
	return (1);
}
