/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 18:57:47 by jniemine          #+#    #+#             */
/*   Updated: 2022/07/20 20:21:35 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

int sort_dispatch(t_file_node *head, int flags)
{
	if (flags & REVERSE_ORDER)
		return (reverse_strcmp(head->file_name, head->next->file_name));
	else if (flags & TIME_ORDER)
		return time_compare(head->stat.st_mtimespec, head->next->stat.st_mtimespec);
	else
		return (ft_strcmp(head->file_name, head->next->file_name));
}

int lst_iter(t_file_node **head, int flags)
{
	t_file_node *temp;
	t_file_node *previous;
	t_file_node *head_local;
	int i;

	i = 0;
	previous = NULL;
	head_local = *head;
	/* Swap the first without previous */
//	debug(*head);
	if (head_local->next && sort_dispatch(head_local, flags) > 0 && ++i)
	{
		temp = head_local->next;
		head_local->next = head_local->next->next;
		temp->next = head_local;
		previous = head_local;
		(*head) = temp;
		head_local = head_local->next;	
	}
	else
	{
		previous = head_local;
		head_local = head_local->next;
	}
	while (head_local)
	{
		if (head_local->next && sort_dispatch(head_local, flags) > 0 && ++i)
		{
//			printf("%s and %s\n", head_local->file_name, head_local->next->file_name);
//			fflush(stdout);
			temp = head_local->next;
			previous->next = head_local->next;
			head_local->next = head_local->next->next;
			temp->next = head_local;
		}
		previous = head_local;
		head_local = head_local->next;
	}
	return (i);
}

void lst_iter_loop(t_file_node **head, int flags)
{
	int i;
	
	i = lst_iter(head, flags);
	while (i)
	{
		i = lst_iter(head, flags);
	}
}

t_file_node *sort(t_file_node **head, int flags)
{
	//What if multiple sorting options are given?
	lst_iter_loop(head, flags);
	return (*head);
}