/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 15:54:43 by jniemine          #+#    #+#             */
/*   Updated: 2021/12/07 14:19:26 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;

	if (n > 0 && src == NULL && dest == NULL)
		return (dest);
	i = 0;
	if (src >= dest)
	{
		while (i < n)
		{
			*(char *)(dest + i) = ((char *)src)[i];
			++i;
		}
		return (dest);
	}
	else
	{
		while (n--)
			((char *)dest)[n] = ((char *)src)[n];
	}
	return (dest);
}
