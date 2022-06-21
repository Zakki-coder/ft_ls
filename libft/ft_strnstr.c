/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strnstr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 17:55:42 by jniemine          #+#    #+#             */
/*   Updated: 2021/11/24 23:50:06 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

char	*ft_strnstr(const char *hs, const char *needle, size_t len)
{
	size_t	ch;
	char	*ret;

	ret = NULL;
	ch = 0;
	if (ft_strlen(needle) == 0)
		return ((char *)hs);
	while (*hs != '\0' && len)
	{
		ret = (char *)hs;
		while (len > 0 && needle[ch] != '\0' && \
				hs[ch] == needle[ch] && hs[ch++] != '\0')
			--len;
		if (needle[ch] == '\0')
			return (ret);
		if (ch > 0)
			hs += ch;
		else
		{
			++hs;
			--len;
		}
		ch = 0;
	}
	return (NULL);
}
