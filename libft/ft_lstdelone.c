/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 18:31:20 by jniemine          #+#    #+#             */
/*   Updated: 2021/11/27 19:32:20 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	ft_lstdelone(t_list **alst, void (*del)(void *, size_t))
{
	if (del == NULL)
		return ;
	del ((*alst)->content, (*alst)->content_size);
	free (*alst);
	*alst = NULL;
}
	//Free the *alst->content of pointer address with del
	//Use free to  free the pointer *alst
	//DO NOT free memory of *alst->next
	//free alst
