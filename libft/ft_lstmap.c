/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 16:31:33 by jniemine          #+#    #+#             */
/*   Updated: 2021/11/29 17:48:11 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*head;
	t_list	*ret;

	if (f == NULL || lst == NULL)
		return (lst);
	head = f(lst);
	ret = head;
	lst = (*lst).next;
	while (lst != NULL)
	{
		(*head).next = f(lst);
		head = (*head).next;
		lst = (*lst).next;
	}
	return (ret);
}
	/* Iterate lst apply funtion to each link make fresh list from pointers
	 */
