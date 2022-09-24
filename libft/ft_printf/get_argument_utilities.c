/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_argument_utilities.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 11:42:36 by jniemine          #+#    #+#             */
/*   Updated: 2022/05/24 17:25:45 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	not_atoi(const char **s)
{
	int	n;

	n = 0;
	while (ft_isdigit(**s))
	{
		n *= 10;
		n += **s - '0';
		++(*s);
	}
	--(*s);
	return (n);
}

unsigned long long	get_argument_u(t_fs *f_str)
{
	int					m;
	unsigned long long	arg;

	m = f_str->modifier;
	if (m & LDBL)
		arg = va_arg(f_str->argcs, long double);
	else if (m & LLONG)
		arg = va_arg(f_str->argcs, unsigned long long int);
	else if (m & LONG)
		arg = va_arg(f_str->argcs, long int);
	else
		arg = va_arg(f_str->argcs, unsigned int);
	return (arg);
}

long long	cast_to_modifier(t_fs *f_str, long long ll)
{
	int	m;

	m = f_str->modifier;
	if (m & LLONG)
		return ((long long)ll);
	else if (m & LONG)
		return ((long)ll);
	else if (m & SIZET)
		return ((size_t)ll);
	else if (m & SHORT)
		return ((short)ll);
	else if (m & CHAR)
		return ((char)ll);
	return ((int)ll);
}

unsigned long long	cast_to_modifier_u(t_fs *f_str, unsigned long long ll)
{
	int	m;

	m = f_str->modifier;
	if (m & LLONG)
		return ((unsigned long long)ll);
	else if (m & LONG)
		return ((unsigned long)ll);
	else if (m & SIZET)
		return ((size_t)ll);
	else if (m & SHORT)
		return ((unsigned short)ll);
	else if (m & CHAR)
		return ((unsigned char)ll);
	return ((unsigned int)ll);
}
