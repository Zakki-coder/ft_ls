/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 19:34:23 by jniemine          #+#    #+#             */
/*   Updated: 2021/12/22 19:13:36 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*res;

	res = ft_memalloc(sizeof(t_list));
	if (res == NULL)
	{
		free (res);
		return (NULL);
	}
	if (!content)
	{
		(*res).content = NULL;
		(*res).content_size = 0;
		(*res).next = NULL;
		return (res);
	}
	(*res).content = ft_memalloc(content_size);
	ft_memcpy((*res).content, content, content_size);
	(*res).content_size = content_size;
	(*res).next = NULL;
	return (res);
}
	/* mallocate and return fresh link
	 * fresh link is initialized with COPY of function params
	 * If param content NULL, set link content NULL and size = 0
	 * link next to NULL
	 * If malloc fail return NULL and ?FREE?	
	 * Wha to do with wrong contetn_size? User responsible? Yes?
	 */
