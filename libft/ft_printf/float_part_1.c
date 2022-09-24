/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float_part_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 18:28:41 by jniemine          #+#    #+#             */
/*   Updated: 2022/05/18 14:44:48 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	set_precision_for_rounding_dir(t_fs *f_str, int *precision)
{
	if (f_str->is_precision)
		*precision = f_str->precision;
	else
	{
		f_str->is_precision = 1;
		f_str->precision = 6;
		*precision += f_str->precision;
	}
}

long double	divide_one_with_ten_n(int precision)
{
	long double	ret;

	ret = 1;
	while (precision)
	{
		ret /= 10;
		--precision;
	}
	return (ret);
}

int	rounding_direction(t_fs *f_str, long double f, int *for_bankers)
{
	int					precision;

	precision = 0;
	set_precision_for_rounding_dir(f_str, &precision);
	if (precision == 0)
		*for_bankers = get_digit_before_decimal(f);
	while (precision > 0)
	{
		f -= (unsigned long long)f;
		f *= 10;
		if (precision == 1)
			*for_bankers = (int)f;
		--precision;
	}
	f -= (unsigned long long)f;
	if (f < 0.5)
		return (-1);
	else if (f == (double)0.5)
		return (0);
	return (1);
}

long double	rounder(t_fs *f_str, long double f)
{
	int			direction;
	int			for_bankers;
	long double	add;

	direction = rounding_direction(f_str, f, &for_bankers);
	if (direction == 1)
	{
		add = divide_one_with_ten_n(f_str->precision);
		f += add;
		f -= add / 10;
		return (f);
	}
	else if (direction == 0)
	{
		if (for_bankers % 2 != 0 || (for_bankers == 0 && f_str->precision > 0))
			f += divide_one_with_ten_n(f_str->precision);
		return (f);
	}
	return (f);
}

void	float_to_ascii(t_fs *f_str)
{
	long double	f;

	if (f_str->modifier & LDBL)
		f = (long double)va_arg(f_str->argcs, long double);
	else
		f = (double)va_arg(f_str->argcs, double);
	if (1 / f < 0)
	{
		f *= -1;
		f_str->neg = 1;
	}
	print_float(f_str, rounder(f_str, f));
	++f_str->str;
}
