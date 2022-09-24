/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hexa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 19:19:34 by jniemine          #+#    #+#             */
/*   Updated: 2022/05/19 18:34:42 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

unsigned int	hexa_len(t_fs *f_str, unsigned long long ull)
{
	char				s[100];
	int					i;
	unsigned long long	zero;

	zero = 0;
	i = 0;
	ft_bzero(s, 100);
	if (ull == 0)
		return (1);
	while (ull > 0)
	{
		if (ull % 16 > 9)
			s[i] = (ull % 16) - 9 + '@';
		else
			s[i] = ull % 16 + '0';
		ull /= 16;
		++i;
	}
	f_str->nb_len += ft_strlen(s);
	return (f_str->nb_len);
}

void	hexa_print(t_fs *f_str, unsigned long long ull)
{
	char	s[100];
	int		i;
	int		casing;

	i = 0;
	ft_bzero(s, 100);
	if (ull == 0)
	{
		f_str->ret += write (1, "0", 1);
		return ;
	}
	if (*f_str->str == 'X')
		casing = '@';
	else
		casing = '`';
	while (ull > 0)
	{
		if (ull % 16 > 9)
			s[i] = (ull % 16) - 9 + casing;
		else
			s[i] = ull % 16 + '0';
		ull /= 16;
		++i;
	}
	f_str->ret += str_reverse(s);
}

void	put_hexa_prefix(t_fs *fs)
{
	char	l_case;

	l_case = *fs->str;
	if (l_case == 'X')
		ft_putstr("0X");
	else
		ft_putstr("0x");
	fs->ret += 2;
}

void	left_adjusted_x(t_fs *f_str, int len, long long nb)
{
	if (f_str->flags & HASH && nb != 0)
	{
		put_hexa_prefix(f_str);
		len += 2;
	}
	f_str->ret += print_zeroes(f_str->precision - len);
	hexa_print(f_str, nb);
	if (len > f_str->precision)
		f_str->precision = len;
	if (f_str->is_precision)
		f_str->ret += print_spaces(f_str->width - f_str->precision);
	else
		f_str->ret += print_spaces(f_str->width - len);
}

void	hexa(t_fs *f_str, long long nb)
{
	int	len;
	int	width;
	int	precision;

	if (*f_str->str != 'p')
	{
		nb = va_arg(f_str->argcs, long long);
		nb = cast_to_modifier_u(f_str, nb);
	}
	if (zero_case(f_str, nb))
		return ;
	if (nb == 0 && f_str->flags & HASH)
		f_str->flags ^= HASH;
	width = f_str->width;
	len = hexa_len(f_str, convert_from_negativity(f_str, nb));
	if (!f_str->is_precision)
		f_str->precision = 1;
	precision = f_str->precision;
	handle_width(f_str, len);
	if (!(f_str->flags & MINUS))
		right_adjusted_x(f_str, nb, len);
	else
		left_adjusted_x(f_str, len, nb);
	++f_str->str;
}
