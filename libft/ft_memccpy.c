/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 02:24:34 by jniemine          #+#    #+#             */
/*   Updated: 2021/11/26 18:20:07 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char		ch;
	unsigned char		*l_dst;
	unsigned const char	*l_src;

	ch = (unsigned char)c;
	l_dst = (unsigned char *)dst;
	l_src = (unsigned const char *)src;
	if (n == 0)
		return (NULL);
	while (n-- && *l_src != ch)
		*l_dst++ = *l_src++;
	if (*l_src == ch)
	{
		*l_dst++ = *l_src++;
		return ((void *)l_dst);
	}
	return (NULL);
}
