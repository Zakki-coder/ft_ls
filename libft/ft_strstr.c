/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 15:22:32 by jniemine          #+#    #+#             */
/*   Updated: 2021/11/25 15:31:35 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	char	*ret;
	size_t	needle_len;

	ret = NULL;
	needle_len = ft_strlen(needle);
	if (*needle == '\0')
		return ((char *)haystack);
	while (*haystack != '\0')
	{
		ret = ft_strchr (haystack, needle[0]);
		if (ret == NULL)
			return (NULL);
		if (!ft_strncmp(ret, needle, needle_len))
			return (ret);
		++haystack;
	}
	return (NULL);
}
