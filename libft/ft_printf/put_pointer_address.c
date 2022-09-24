/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_pointer_address.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 15:12:05 by jniemine          #+#    #+#             */
/*   Updated: 2022/05/18 15:17:41 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	hexa_wrapper(t_fs *f_str, unsigned long long address)
{
	int	precision;
	int	width;
	int	is_precision;

	precision = f_str->precision;
	width = f_str->width;
	is_precision = f_str->is_precision;
	f_str->is_precision = 0;
	f_str->width = 0;
	f_str->precision = 0;
	hexa(f_str, address);
	f_str->is_precision = is_precision;
	f_str->width = width;
	f_str->precision = precision;
}

void	right_adjusted_pointer_address(t_fs *fs, int len)
{
	int	precision_temp;

	precision_temp = fs->precision;
	if (!(fs->flags & MINUS))
	{
		if (fs->flags & ZERO)
		{
			if (!fs->is_precision)
				fs->precision = fs->width - 2;
			fs->ret += print_spaces(fs->width - fs->precision - 2);
		}
		else
		{
			if (fs->precision < len)
				precision_temp = len;
			fs->ret += print_spaces(fs->width - precision_temp - 2);
		}
	}
}

void	put_pointer_address(t_fs *f_str)
{
	unsigned long long	address;
	void				*void_argument;
	int					len;

	void_argument = va_arg(f_str->argcs, void *);
	address = (unsigned long long)void_argument;
	len = hexa_len(f_str, address);
	if (!(f_str->flags & MINUS))
		right_adjusted_pointer_address(f_str, len);
	f_str->ret += write(1, "0x", 2);
	if (f_str->is_precision || f_str->flags & ZERO)
		f_str->ret += print_zeroes(f_str->precision - len);
	if (address == 0 && (!(f_str->is_precision) || f_str->precision > 0))
			f_str->ret += write(1, "0", 1);
	if (address != 0)
		hexa_wrapper(f_str, address);
	else
		++(f_str->str);
	if (f_str->flags & MINUS)
		f_str->ret += print_spaces(f_str->width - len - 2);
}
