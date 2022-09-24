/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 13:47:41 by jniemine          #+#    #+#             */
/*   Updated: 2021/11/29 14:53:55 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd(t_list **alst, t_list *new)
{
	t_list	*new_next;

	if (new == NULL || alst == NULL)
		return ;
	new_next = *alst;
	*alst = new;
	(*new).next = new_next;
}
	/* Add element new at beginning of list
	 * Test with NULL input
	 */
