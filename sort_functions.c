/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 18:57:24 by jniemine          #+#    #+#             */
/*   Updated: 2022/09/23 13:58:40 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

int	reverse_strcmp(const char *s1, const char *s2)
{
	return (-1 * ft_strcmp(s1, s2));
}

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

void	reverse_lst(t_file_node **head)
{
	t_file_node	*last;
	t_file_node	*l_head;
	t_file_node	*next;

	if (!((*head)->next))
		return ;
	l_head = *head;
	next = NULL;
	last = l_head;
	l_head = l_head->next;
	last->next = NULL;
	if (l_head && l_head->next)
		next = l_head->next;
	l_head->next = last;
	while (l_head && next)
	{
		last = l_head;
		l_head = next;
		next = l_head->next;
		l_head->next = last;
	}
	*head = l_head;
}
