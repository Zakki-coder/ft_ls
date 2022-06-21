/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   beta_ft_putnbr_fd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 13:06:16 by jniemine          #+#    #+#             */
/*   Updated: 2021/11/23 13:09:30 by jniemine         ###   ########.fr       */
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

void	ft_putnbr_fd(int n, int fd)
{
	int	len;

	len = length(n);
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		if (n == -2147483648)
		{
			ft_putstr_fd("2147483648", fd);
			return ;
		}
		n *= -1;
	}
	while (len)
	{
		ft_putchar_fd(((n / ex(len)) + '0'), fd);
		n -= n / ex(len) * ex(len);
		--len;
	}	
}
