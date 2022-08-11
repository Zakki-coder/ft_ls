/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 18:57:47 by jniemine          #+#    #+#             */
/*   Updated: 2022/08/09 15:36:51 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

int sort_dispatch(t_file_node *head, int flags, t_width *widths)
{
	if (flags & TIME_ORDER)
		return time_compare(head->stat, head->next->stat);
	else if (flags & REVERSE_ORDER)
	{
		if (widths->is_file)
			return (reverse_strcmp(head->path, head->next->path));
		return (reverse_strcmp(head->file_name, head->next->file_name));
	}
	else
	{
		if (widths->is_file)
			return (ft_strcmp(head->path, head->next->path));
		return (ft_strcmp(head->file_name, head->next->file_name));
	}
}

int lst_iter(t_file_node **head, int flags, t_width *widths)
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
	if (head_local->next && sort_dispatch(head_local, flags, widths) > 0 && ++i)
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
		if (head_local->next && sort_dispatch(head_local, flags, widths) > 0 && ++i)
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

void lst_iter_loop(t_file_node **head, int flags, t_width *widths)
{
	int i;
	
	i = lst_iter(head, flags, widths);
	while (i)
	{
		i = lst_iter(head, flags, widths);
	}
}

t_file_node *sort(t_file_node **head, int flags, t_width *widths)
{
	//What if multiple sorting options are given?
	lst_iter_loop(head, flags, widths);
	(*head)->is_head = 1;
	return (*head);
}