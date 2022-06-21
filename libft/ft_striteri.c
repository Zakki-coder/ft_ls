/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   beta_ft_striteri.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 15:08:02 by jniemine          #+#    #+#             */
/*   Updated: 2021/11/16 15:29:39 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	int	index;

	if (s == NULL || f == NULL)
		return ;
	index = 0;
	while (s[index])
	{
		f(index, s + index);
		++index;
	}
	return ;
}
