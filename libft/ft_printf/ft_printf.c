/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 12:27:41 by jniemine          #+#    #+#             */
/*   Updated: 2022/05/19 14:44:11 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

unsigned long long	print_spaces(int len)
{
	unsigned long long	ret;

	ret = 0;
	while (len > 0)
	{
		ft_putchar(' ');
		--len;
		++ret;
	}
	return (ret);
}

unsigned long long	print_zeroes(int len)
{
	unsigned long long	ret;

	ret = 0;
	while (len > 0)
	{
		ft_putnbr(0);
		--len;
		++ret;
	}
	return (ret);
}

void	format_fs(t_fs *f_str)
{
	f_str->flags = 0;
	f_str->width = 0;
	f_str->precision = 0;
	f_str->is_precision = 0;
	f_str->modifier = 0;
	f_str->conversion = 0;
	f_str->neg = 0;
	f_str->percent_flag = 0;
	f_str->nb_len = 0;
}

int	str_reverse(char *s)
{
	int		len;
	int		i;
	char	temp[100];

	bzero(temp, 100);
	len = ft_strlen(s) - 1;
	i = 0;
	while (len >= 0)
	{
		temp[i] = s[len];
		++i;
		--len;
	}
	ft_putstr(temp);
	return (ft_strlen(temp));
}

int	ft_printf(const char *str, ...)
{
	t_fs	f_str;

	format_fs(&f_str);
	f_str.ret = 0;
	f_str.str = str;
	va_start(f_str.argcs, str);
	parser(&f_str);
	va_end(f_str.argcs);
	return (f_str.ret);
}
