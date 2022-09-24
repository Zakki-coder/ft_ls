/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_format_utilities.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 19:20:57 by jakken            #+#    #+#             */
/*   Updated: 2022/05/19 16:01:09 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	get_modifiers(t_fs *f_str, const char *format)
{
	while (*format != '\0')
	{
		if (*format == 'L')
			f_str->modifier |= LDBL;
		if (*format == 'l' && *(format + 1) == 'l')
			f_str->modifier |= LLONG;
		if ((*format == 'l' && *(format - 1) != 'l'
				&& *(format + 1) != 'l') || *format == 'U')
			f_str->modifier |= LONG;
		if (*format == 'j')
			f_str->modifier |= LLONG;
		if (*format == 'z')
			f_str->modifier |= LLONG;
		if (*format == 'h' && *(format + 1) == 'h'
			&& *(format - 1) != 'h' && *(format + 2) != 'h' && (format)++)
			f_str->modifier |= CHAR;
		else if (*format == 'h')
			f_str->modifier |= SHORT;
		++format;
	}
}

static void	get_precision_with_star(t_fs *f_str)
{
	int	n;

	n = (int)va_arg(f_str->argcs, int);
	if (n >= 0)
	{
		f_str->precision = n;
		f_str->is_precision = 1;
	}
}

void	get_precision(t_fs *f_str, const char *format)
{
	long int	n;

	n = 0;
	while (*format != '\0')
	{
		++format;
		if (*format == '.' && *(format + 1) != '*')
		{
			f_str->is_precision = 1;
			while (*format == '.')
				++(format);
			if (ft_isdigit(*format))
			{
				n = not_atoi(&format);
				if (n > f_str->precision && n <= MAX_INT)
					f_str->precision = n;
			}
			else
				f_str->precision = 0;
		}
		else if (*format == '*' && *(format - 1) == '.')
			get_precision_with_star(f_str);
	}
}

void	get_width(t_fs *f_str, const char *format)
{
	long int	n;

	n = 0;
	while (*format != '\0')
	{
		++format;
		if (*format == '.' && ++format)
			while (ft_isdigit(*format))
				++format;
		if (ft_isdigit(*format) && *(format - 1) != '.' && *format != '0')
		{
			n = not_atoi(&format);
			if (n <= MAX_INT)
				f_str->width = n;
		}
		else if (*format == '*' && *(format - 1) != '.')
		{
			n = (int)va_arg(f_str->argcs, int);
			if (n < 0)
				f_str->flags |= MINUS;
			if (n < 0)
				n *= -1;
			f_str->width = n;
		}
	}
}

void	get_flags(t_fs *f_str, char *fs)
{
	int			*flags;

	flags = &f_str->flags;
	if (ft_strchr(fs, '#'))
		*flags |= HASH;
	if (ft_strchr(fs, '-'))
		*flags |= MINUS;
	if (ft_strchr(fs, '0') && !(ft_isdigit(*(ft_strchr(fs, '0') - 1)))
		&& *(ft_strchr(fs, '0') - 1) != '.')
		*flags |= ZERO;
	if (ft_strchr(fs, '+'))
		*flags |= PLUS;
	if (ft_strchr(fs, ' '))
		*flags |= SPACE;
}
