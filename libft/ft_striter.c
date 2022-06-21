/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   beta_ft_striter.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 13:54:44 by jniemine          #+#    #+#             */
/*   Updated: 2021/11/16 14:36:09 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	ft_striter(char *s, void (*f)(char *))
{
	if (s == NULL || f == NULL)
		return ;
	while (*s)
	{
		f(s);
		++s;
	}
	return ;
}
