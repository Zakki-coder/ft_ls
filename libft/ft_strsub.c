/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   beta_ft_strsub.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 18:33:10 by jniemine          #+#    #+#             */
/*   Updated: 2021/11/16 19:55:33 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	char	*r_sub;

	sub = malloc(sizeof(*sub) * len + 1);
	r_sub = sub;
	if (sub == NULL || s == NULL)
		return (NULL);
	s += start;
	while (len--)
		*sub++ = *s++;
	*sub = '\0';
	return (r_sub);
}
