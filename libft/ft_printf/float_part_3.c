/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float_part_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 18:48:38 by jniemine          #+#    #+#             */
/*   Updated: 2022/05/13 18:48:40 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

long double	ten_raised_to_n(unsigned int n)
{
	long double	res;

	res = 1;
	while (n > 0)
	{
		res *= 10;
		--n;
	}
	return (res);
}

int	get_digit_before_decimal(long double f)
{
	unsigned long long	nb;

	nb = f;
	if (nb > 10)
	{
		nb /= 10;
		nb *= 10;
		nb = (unsigned long long)f - nb;
		return ((int)nb);
	}
	return ((int)f);
}
