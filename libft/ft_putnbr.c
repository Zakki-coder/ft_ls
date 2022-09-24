/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   beta_ft_putnbr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 14:13:48 by jniemine          #+#    #+#             */
/*   Updated: 2021/11/22 16:05:54 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	length(int n)
{
	int	len;

	len = 0;
	if (n == 0)
		return (1);
	while (n)
	{
		++len;
		n /= 10;
	}
	return (len);
}

static int	ex(int len)
{
	int	res;

	res = 1;
	while (--len)
		res *= 10;
	return (res);
}

void	ft_putnbr(int n)
{
	int	len;

	len = length(n);
	if (n < 0)
	{
		ft_putchar('-');
		if (n == -2147483648)
		{
			ft_putstr("2147483648");
			return ;
		}
		n *= -1;
	}
	while (len)
	{
		ft_putchar(((n / ex(len)) + '0'));
		n -= n / ex(len) * ex(len);
		--len;
	}	
}
