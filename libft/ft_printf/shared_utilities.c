/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shared_utilities.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 12:13:53 by jniemine          #+#    #+#             */
/*   Updated: 2022/05/18 14:40:10 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	handle_width(t_fs *f_str, int len)
{
	int		f;

	f = f_str->flags;
	if (len > f_str->width)
		f_str->width = len;
	if (f_str->precision > f_str->width)
		f_str->width = f_str->precision;
	if (len == f_str->width && has_prefix(f_str))
		if ((*f_str->str == 'd' || *f_str->str == 'i')
			&& f_str->width < MAX_INT)
			++f_str->width;
	if ((!(f & MINUS)) && has_prefix(f_str) && f_str->precision == f_str->width)
		++f_str->width;
}

int	has_prefix(t_fs *f_str)
{
	int		f;
	char	c;

	c = *f_str->str;
	f = f_str->flags;
	if (c == 'd' || c == 'i' || c == 'f')
		return (f_str->neg || f & SPACE || f & PLUS);
	else
		return (0);
}

unsigned long long	convert_from_negativity(t_fs *f_str, long long ll)
{
	unsigned long long	ull;
	char				c;

	c = *f_str->str;
	ull = 0;
	if ((c == 'd' || c == 'i' || c == 'f') && ll < 0)
	{
		f_str->neg = 1;
		if (ll == -9223372036854775807 - 1)
			ull = (unsigned long long)9223372036854775807 + 1;
		else
			ull = ll * -1;
		return (ull);
	}
	ull = ll;
	return (ull);
}

int	zero_case(t_fs *f_str, unsigned long long ull)
{
	if (ull == 0 && f_str->is_precision && f_str->precision == 0)
	{
		if (f_str->flags & PLUS)
		{
			f_str->ret += print_spaces(f_str->width - 1);
			f_str->ret += write(1, "+", 1);
		}
		else
			f_str->ret += print_spaces(f_str->width);
		++f_str->str;
		return (1);
	}
	return (0);
}

void	set_prefix(t_fs *f_str, char *out, unsigned int nb_len)
{
	int		f;
	char	prefix;

	f = f_str->flags;
	if (*f_str->str == 'f')
		f_str->precision = nb_len;
	if (f_str->neg)
		prefix = '-';
	else if (f & PLUS)
		prefix = '+';
	else if (f & SPACE)
		prefix = ' ';
	else
		return ;
	if (!(f & MINUS) && f & ZERO && !f_str->is_precision)
		f_str->precision = f_str->width - 1;
	if ((f & MINUS))
		*out = prefix;
	else if (*f_str->str == 'f' && f & ZERO && !(f & MINUS))
		*(out + f_str->width - f_str->precision) = prefix;
	else
		*(out + f_str->width - f_str->precision - 1) = prefix;
}
