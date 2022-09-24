/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   beta_ft_memchr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 14:59:38 by jniemine          #+#    #+#             */
/*   Updated: 2021/11/23 20:43:41 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*u_s;
	unsigned char	u_c;

	u_s = (unsigned char *)s;
	u_c = (unsigned char)c;
	while (--n && *u_s != u_c)
		++u_s;
	if (*u_s == u_c)
		return ((void *)u_s);
	return (NULL);
}
