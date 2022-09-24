/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   beta_ft_strmap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 16:01:20 by jniemine          #+#    #+#             */
/*   Updated: 2021/11/23 22:57:12 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>
#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char	*res;
	int		i;

	i = 0;
	if (s == NULL || f == NULL)
		return (NULL);
	res = malloc(ft_strlen(s) + 1);
	if (res == NULL)
		return (NULL);
	while (s[i])
	{
		res[i] = f(s[i]);
		++i;
	}
	res[i] = '\0';
	return (res);
}
