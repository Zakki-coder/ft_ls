/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 16:42:32 by jniemine          #+#    #+#             */
/*   Updated: 2021/11/24 23:58:40 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t				i;
	const unsigned char	*l_s1;
	const unsigned char	*l_s2;

	l_s2 = (const unsigned char *)s2;
	l_s1 = (const unsigned char *)s1;
	i = 0;
	if (n == 0)
		return (0);
	while (l_s1[i] == l_s2[i] && i < n && l_s1[i] != '\0' && l_s2[i] != '\0')
	{
		if (i + 1 == n)
			return (l_s1[i] - l_s2[i]);
		++i;
	}
	return (l_s1[i] - l_s2[i]);
}
