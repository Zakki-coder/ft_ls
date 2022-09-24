/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   octal_part_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 21:42:37 by jniemine          #+#    #+#             */
/*   Updated: 2022/05/18 21:56:10 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

unsigned int	octal_print(unsigned long long ull)
{
	char	s[100];
	int		i;

	if (ull == 0)
	{
		ft_putnbr(0);
		return (1);
	}
	i = 0;
	ft_bzero(s, 100);
	while (ull > 0)
	{
		s[i] = (ull % 8) + '0';
		ull /= 8;
		++i;
	}
	return (str_reverse(s));
}

static void	right_adj_has_precision(t_fs *fs, unsigned long long ull, int len)
{
	if (fs->precision > len)
		fs->ret += print_spaces(fs->width - fs->precision);
	else
		fs->ret += print_spaces(fs->width - len);
	if (ull == 0 || fs->flags & HASH)
		fs->ret += print_zeroes(1);
	fs->ret += print_zeroes(fs->precision - len);
}

void	r_adjusted_octal(t_fs *fs, unsigned long long ull, int len)
{
	if (fs->precision > 0)
		right_adj_has_precision(fs, ull, len);
	else if (!fs->is_precision)
	{			
		if (!(fs->flags & ZERO))
			fs->ret += print_spaces(fs->width - fs->precision - len);
		if (fs->flags & HASH)
			fs->ret += print_zeroes(1);
		if (fs->flags & ZERO)
			fs->ret += print_zeroes(fs->width - len);
	}
	else if (fs->is_precision)
	{		
		fs->ret += print_spaces(fs->width - fs->precision - len);
		if (fs->flags & HASH && ++len)
			fs->ret += print_zeroes(1);
	}
	if (ull > 0 || (ull == 0 && !fs->is_precision && !(fs->flags & HASH)))
		fs->ret += octal_print(ull);
	++fs->str;
}
