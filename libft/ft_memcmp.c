/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   beta_ft_memcmp.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 14:59:19 by jniemine          #+#    #+#             */
/*   Updated: 2021/11/24 21:09:19 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*l1;
	const unsigned char	*l2;

	l1 = s1;
	l2 = s2;
	if (n == 0)
		return (0);
	while (--n && *l1 == *l2)
	{
		++l1;
		++l2;
	}
	return ((int)(*l1 - *l2));
}
