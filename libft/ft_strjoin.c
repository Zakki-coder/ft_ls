/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   beta_ft_strjoin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 20:02:15 by jniemine          #+#    #+#             */
/*   Updated: 2021/11/16 20:22:57 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h" 

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*res;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	res = malloc(sizeof(*res) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (res == NULL)
		return (NULL);
	ft_strcpy(res, s1);
	ft_strcat(res, s2);
	return (res);
}
