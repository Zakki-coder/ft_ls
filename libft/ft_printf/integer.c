/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   integer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 22:03:25 by jniemine          #+#    #+#             */
/*   Updated: 2022/05/19 16:18:01 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	nb_length(unsigned long long nb)
{
	int	n;

	n = 0;
	if (nb == 0)
		return (1);
	while (nb)
	{
		++n;
		nb /= 10;
	}
	return (n);
}

static void	get_argument_wrap(t_fs *f_str, unsigned long long *ull)
{
	if (*f_str->str == 'U')
		f_str->modifier |= LONG;
	*ull = get_argument_u(f_str);
}

unsigned long long	get_int_argument(t_fs *f_str)
{
	unsigned long long	ull;
	long long			ll;

	ull = 0;
	ll = 0;
	if (*f_str->str == 'u' || *f_str->str == 'U')
	{
		get_argument_wrap(f_str, &ull);
		if (*f_str->str == 'u' || *f_str->str == 'U')
		{
			if (f_str->flags & PLUS)
				f_str->flags ^= PLUS;
			if (f_str->flags & SPACE)
				f_str->flags ^= SPACE;
		}
		ull = cast_to_modifier_u(f_str, ull);
	}
	else
	{
		ll = get_argument_u(f_str);
		ll = cast_to_modifier(f_str, ll);
		ull = convert_from_negativity(f_str, ll);
	}
	return (ull);
}

void	integer_split(t_fs *f_str, int *prefix, char *out, int len)
{
	int	width;
	int	precision;

	width = f_str->width;
	precision = f_str->precision;
	if (f_str->flags & MINUS)
	{
		*prefix = 0;
		if (f_str->flags & PLUS || f_str->flags & SPACE || f_str->neg)
			*prefix = 1;
		if (precision - len > 0)
		{
			ft_memset(out + *prefix, '0', precision - len);
			*prefix += precision - len;
		}
	}
	if (!(f_str->flags & MINUS) && f_str->is_precision)
		ft_memset(out + (width - precision), '0', precision);
	else if (!(f_str->flags & MINUS) && f_str->flags & ZERO)
		ft_memset(out, '0', width);
}

void	integer(t_fs *f_str)
{
	char				*out;
	int					len;
	int					prefix;
	unsigned long long	ull;

	ull = get_int_argument(f_str);
	if (zero_case(f_str, ull))
		return ;
	len = nb_length(ull);
	handle_width(f_str, len);
	if (f_str->precision < len)
		f_str->precision = len;
	prefix = f_str->width - len;
	out = (char *)ft_memalloc(sizeof(*out) * f_str->width + 1);
	if (out == NULL)
		exit (-1);
	ft_memset(out, ' ', f_str->width);
	integer_split(f_str, &prefix, out, len);
	out = s_itoa(out, ull, len, prefix);
	set_prefix(f_str, out, len);
	if ((prefix + len) > f_str->width)
		f_str->width = prefix + len;
	f_str->ret += write(1, out, f_str->width);
	++f_str->str;
	free(out);
}
