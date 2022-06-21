/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 23:49:39 by jniemine          #+#    #+#             */
/*   Updated: 2021/11/27 19:36:37 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*temp_next;
	t_list	**temp_next_null;

	temp_next = (**alst).next;
	temp_next_null = &(**alst).next;
	if (del == NULL)
		return ;
	del((**alst).content, (**alst).content_size);
	free (*alst);
	if (*temp_next_null == NULL)
		return ;
	ft_lstdel(&temp_next, del);
	*temp_next_null = NULL;
	*alst = NULL;
	return ;
}
	/* Parameter is beginning of list to be freed, not head necessarily
	 * free it and every successor with del for content and free for link 
	 * free also previous link pointers next pointer
	 * Maybe take account of void pointers as parameter.
	 */
