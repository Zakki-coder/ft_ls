/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_string.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 15:12:13 by jniemine          #+#    #+#             */
/*   Updated: 2022/05/18 16:11:46 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	null_string(t_fs *fs, char *s)
{
	if (fs->flags & MINUS && fs->str++)
	{
		if (fs->is_precision)
			fs->ret += ft_printf("%-*.*s", fs->width, fs->precision, s);
		else
			fs->ret += ft_printf("%-*s", fs->width, s);
	}
	else
	{
		if (fs->is_precision)
		{
			if (fs->flags & ZERO)
				fs->ret += ft_printf("%0*.*s", fs->width, fs->precision, s);
			else
				fs->ret += ft_printf("%*.*s", fs->width, fs->precision, s);
		}
		else
		{
			if (fs->flags & ZERO)
				fs->ret += ft_printf("%0*s", fs->width, s);
			else
				fs->ret += ft_printf("%*s", fs->width, s);
		}
	}
	return (1);
}

void	put_string(t_fs *f_str)
{
	const char			*str;
	int					len;

	str = va_arg(f_str->argcs, const char *);
	if (str == 0 && null_string(f_str, "(null)"))
		return ;
	len = ft_strlen(str);
	if (f_str->precision < 0)
		f_str->precision = 0;
	if (f_str->is_precision && f_str->precision < len)
		len = f_str->precision;
	if (f_str->width > len && !(f_str->flags & MINUS))
	{
		if (f_str->flags & ZERO)
			f_str->ret += print_zeroes(f_str->width - len);
		else
			f_str->ret += print_spaces(f_str->width - len);
	}
	f_str->ret += write(1, str, len);
	if (f_str->width > len && f_str->flags & MINUS)
		f_str->ret += print_spaces(f_str->width - len);
	++f_str->str;
	return ;
}

void	put_character(t_fs *f_str)
{
	unsigned char	ch;

	if (f_str->width >= 1)
		f_str->width -= 1;
	if (!(f_str->flags & MINUS))
	{
		if (f_str->flags & ZERO)
			f_str->ret += print_zeroes(f_str->width);
		else
			f_str->ret += print_spaces(f_str->width);
	}
	ch = (unsigned char)va_arg(f_str->argcs, int);
	if (ch == 0)
		f_str->ret += write(1, "\0", 1);
	else
		f_str->ret += write(1, &ch, 1);
	if (f_str->flags & MINUS)
		f_str->ret += print_spaces(f_str->width);
	++f_str->str;
}
