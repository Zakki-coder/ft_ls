/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 13:18:38 by jniemine          #+#    #+#             */
/*   Updated: 2022/09/13 00:20:42 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

int	sort_dispatch(t_file_node *head, int flags, t_width *widths)
{
	if (flags & TIME_ORDER)
		return (time_compare(head->stat, head->next->stat));
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

int	iter_split(t_file_node *head, t_file_node *prev, int flags, t_width *widths)
{
	t_file_node	*temp;
	int			i;

	i = 0;
	while (head)
	{
		if (head->next && sort_dispatch(head, flags, widths) > 0
			&& ++i)
		{
			temp = head->next;
			prev->next = head->next;
			head->next = head->next->next;
			temp->next = head;
		}
		prev = head;
		head = head->next;
	}
	return (i);
}

int	lst_iter(t_file_node **head, int flags, t_width *widths)
{
	t_file_node	*temp;
	t_file_node	*previous;
	t_file_node	*head_local;
	int			i;

	i = 0;
	previous = NULL;
	head_local = *head;
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
	return (iter_split(head_local, previous, flags, widths) + i);
}

void	lst_iter_loop(t_file_node **head, int flags, t_width *widths)
{
	int	i;

	i = lst_iter(head, flags, widths);
	while (i)
	{
		i = lst_iter(head, flags, widths);
	}
}

t_file_node	*sort(t_file_node **head, int flags, t_width *widths)
{
	while (*head != NULL && !(widths->flags & ALL)
		&& (*head)->is_hidden)
	{
		(*head)->is_head = 0;
		*head = (*head)->next;
		if (*head)
			(*head)->is_head = 1;
	}
	if (*head != NULL)
	{
	//	*head = (*head)->next;
		(*head)->is_head = 0;
		if (flags & TIME_ORDER)
			lst_iter_loop(head, 0, widths);
		lst_iter_loop(head, flags, widths);
		(*head)->is_head = 1;
	}
	return (*head);
}
