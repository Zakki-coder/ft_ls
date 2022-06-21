/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 17:57:29 by jniemine          #+#    #+#             */
/*   Updated: 2021/11/24 23:36:05 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	char	*l_src;
	char	*l_dst;
	size_t	dst_len;
	size_t	ret;

	l_src = (char *)src;
	dst_len = ft_strlen(dst);
	l_dst = dst + dst_len;
	ret = 0;
	if (dstsize > dst_len)
		ret = ft_strlen(src) + dst_len;
	else
		ret = ft_strlen(src) + dstsize;
	while (*l_src && l_src < (src + (dstsize - dst_len - 1)))
		*l_dst++ = *l_src++;
	*l_dst = '\0';
	return (ret);
}
/*
 * append src to end of dst
 * append at most dstsize - strlen(dst) - 1 char
 * NUL terminate unless dstsize is 0 or original dst was longer than dstsize
 * return initial length of dst + length of source
 */
