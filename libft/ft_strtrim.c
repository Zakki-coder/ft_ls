/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   beta_ft_strtrim.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 11:14:13 by jniemine          #+#    #+#             */
/*   Updated: 2021/11/25 02:10:20 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static char	*clr_leading(char const **s)
{
	while (**s != '\0' && ((**s == 9 || **s == 10 || **s == 32)
			&& (*(*s + 1) == 9 || *(*s + 1) == 10 || *(*s + 1) == 32)))
		++(*s);
	if (**s != '\0' && (**s == 9 || **s == 10 || **s == 32))
		++(*s);
	return ((char *)*s);
}

static char	*clr_trailing(char const **s, char *begin)
{
	while ((*s - 1) >= begin && ((**s == 9 || **s == 10 || **s == 32)
			&& (*(*s - 1) == 9 || *(*s - 1) == 10 || *(*s - 1) == 32)))
		--(*s);
	if ((*s - 1) >= begin && (**s == 9 || **s == 10 || **s == 32))
		--(*s);
	return ((char *)*s);
}	

char	*ft_strtrim(char const *s)
{
	char	*res;
	char	*start;
	char	*end;
	char	*s_temp;
	char	*r_temp;

	s_temp = (char *)s;
	if (s == NULL)
		return (NULL);
	start = clr_leading(&s);
	while (*s != '\0' && *(s + 1) != '\0')
		++s;
	end = clr_trailing(&s, start);
	res = malloc(sizeof(*res) * (end - start) + 2);
	if (res == NULL)
		return (NULL);
	r_temp = res;
	while (start <= end)
		*res++ = *start++;
	*res = '\0';
	if (!ft_strcmp(s_temp, r_temp))
		return (ft_strcpy(r_temp, s_temp));
	return (r_temp);
}
