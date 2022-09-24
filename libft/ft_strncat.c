/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 16:17:43 by jniemine          #+#    #+#             */
/*   Updated: 2021/11/23 21:17:24 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

char	*ft_strncat(char *s1, const char *s2, size_t n)
{
	char	*l_s1;

	l_s1 = s1;
	l_s1 = l_s1 + ft_strlen(l_s1);
	while (n-- && *s2)
		*l_s1++ = *s2++;
	*l_s1 = '\0';
	return (s1);
}
