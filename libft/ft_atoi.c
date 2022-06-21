/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   beta_ft_atoi.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 15:00:23 by jniemine          #+#    #+#             */
/*   Updated: 2021/11/25 00:58:23 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_forbidden(const char *nptr)
{
	char	c;

	c = nptr[0];
	if (!((c >= 9 && c <= 13) || c == 32 \
		|| (c >= 48 && c <= 57) || c == 43 || c == 45))
		return (1);
	return (0);
}

int	ft_atoi(const char *nptr)
{
	int		sign;
	int		res;

	res = 0;
	sign = 1;
	if (is_forbidden(nptr))
		return (0);
	while (*nptr >= 9 && *nptr <= 32)
		++nptr;
	if ((!ft_isdigit(*nptr) && !ft_isdigit(*(nptr + 1))))
		return (0);
	if (is_forbidden(nptr))
		return (0);
	if (*nptr == '-')
		sign *= -1;
	if (!ft_isdigit(*nptr))
		++nptr;
	while (ft_isdigit(*nptr) && *nptr)
	{
		res *= 10;
		res += *nptr - '0';
		++nptr;
	}
	return (sign * res);
}		
