/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hexa_part_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 20:43:45 by jniemine          #+#    #+#             */
/*   Updated: 2022/05/19 18:27:30 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	right_adjusted_no_precision(t_fs *fs, unsigned long long ull, int len)
{
	if (!(fs->flags & ZERO))
	{
		if (fs->flags & HASH)
			len += 2;
		fs->ret += print_spaces(fs->width - len);
	}
	if (fs->flags & HASH && ull != 0)
	{
		len += 2;
		put_hexa_prefix(fs);
	}
	if (fs->flags & ZERO)
		fs->ret += print_zeroes(fs->width - len);
}

void	right_adjusted_has_precision(t_fs *fs, unsigned long long ull, int len)
{
	if (fs->flags & HASH)
	{
		len += 2;
		fs->ret += print_spaces(fs->width - fs->precision - len);
		if (ull > 0)
			put_hexa_prefix(fs);
	}
	else
		fs->ret += print_spaces(fs->width - fs->precision - len);
}

void	right_adjusted_x(t_fs *fs, unsigned long long ull, int len)
{
	if (fs->is_precision && fs->precision > 0)
	{
		if (fs->flags & HASH)
			fs->width -= 2;
		if (fs->precision > len)
			fs->ret += print_spaces(fs->width - fs->precision);
		else
			fs->ret += print_spaces(fs->width - len);
		if (fs->flags & HASH && ull > 0)
			put_hexa_prefix(fs);
		fs->ret += print_zeroes(fs->precision - len);
	}
	else if (!fs->is_precision)
		right_adjusted_no_precision(fs, ull, len);
	else if (fs->is_precision)
		right_adjusted_has_precision(fs, ull, len);
	if (ull > 0 || ((ull == 0 && fs->precision > 0)))
		hexa_print(fs, ull);
}
