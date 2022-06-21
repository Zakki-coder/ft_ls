/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelany.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 16:59:36 by jniemine          #+#    #+#             */
/*   Updated: 2021/12/22 17:11:57 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	ft_lstdelany(t_list **head, t_list *del)
{
	t_list	*prev;
	t_list	*temp_head;

	temp_head = *head;
	prev = NULL;
	if (temp_head == del)
		*head = (temp_head)->next;
	while (temp_head != NULL && temp_head != del)
	{
		prev = temp_head;
		temp_head = (temp_head)->next;
	}
	if (temp_head == del)
	{
		if (prev != NULL)
			prev->next = temp_head->next;
		free((temp_head)->content);
		(temp_head)->content_size = 0;
		(temp_head)->content = NULL;
		(temp_head)->next = NULL;
	}
}
/* 
 * Takes address of lst head and lst node to be deleted as param
 */
