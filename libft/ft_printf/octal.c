/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   octal.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 21:05:20 by jniemine          #+#    #+#             */
/*   Updated: 2022/05/18 21:56:00 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static unsigned int	octal_len(t_fs *f_str, unsigned long long ull)
{
	char	s[100];
	int		i;
	int		add;

	add = 0;
	i = 0;
	ft_bzero(s, 100);
	if (ull == 0)
		return (1);
	while (ull > 0)
	{
		s[i] = (ull % 8) + '0';
		ull /= 8;
		++i;
	}
	if (f_str->flags & HASH)
		add = 1;
	return (ft_strlen(s) + add);
}

static unsigned long long	get_octa_argument(t_fs *f_str)
{
	unsigned long long	ull;

	ull = 0;
	ull = get_argument_u(f_str);
	ull = cast_to_modifier_u(f_str, ull);
	return (ull);
}

static void	left_adjusted_octal(t_fs *f_str, unsigned long long ull, int len)
{
	if (f_str->flags & HASH)
		f_str->ret += print_zeroes(1);
	if (len > f_str->precision)
		f_str->precision = len;
	if (ull > 0)
		f_str->ret += print_zeroes(f_str->precision - len);
	else if (ull == 0 && f_str->precision > 0)
		f_str->ret += print_zeroes(f_str->precision - len + 1);
	if (ull > 0)
		f_str->ret += octal_print(ull);
	f_str->ret += print_spaces(f_str->width - f_str->precision);
	++f_str->str;
}

void	octal(t_fs *f_str)
{
	int					len;
	int					width;
	int					precision;
	unsigned long long	ull;

	ull = get_octa_argument(f_str);
	if (ull == 0 && f_str->is_precision && f_str->precision == 0)
	{
		if (f_str->flags & HASH)
			f_str->width -= 1;
		if (f_str->flags & HASH && f_str->flags & MINUS)
			f_str->ret += print_zeroes(1);
		zero_case(f_str, ull);
		if (f_str->flags & HASH && !(f_str->flags & MINUS))
			f_str->ret += print_zeroes(1);
		return ;
	}
	width = f_str->width;
	precision = f_str->precision;
	len = octal_len(f_str, ull);
	handle_width(f_str, len);
	if (!(f_str->flags & MINUS))
		r_adjusted_octal(f_str, ull, len);
	else
		left_adjusted_octal(f_str, ull, len);
}
