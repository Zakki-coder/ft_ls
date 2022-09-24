/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   percent.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 11:09:26 by jniemine          #+#    #+#             */
/*   Updated: 2022/05/18 19:02:44 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	right_adjusted_percent(t_fs *f_str)
{
	char	*percent;
	char	*percent_temp;
	int		count;

	count = 0;
	if (f_str->flags & ZERO)
		f_str->ret += print_zeroes(f_str->width - 1);
	else
		f_str->ret += print_spaces(f_str->width - 1);
	f_str->ret += write (1, "%", 1);
	percent = ft_strchr(f_str->str + 1, '%');
	percent_temp = percent;
	while (percent_temp)
	{
		percent_temp = ft_strchr(percent_temp + 1, '%');
		++count;
	}
	if (count == 1 && !search_conversion(percent + 1))
	{
		f_str->ret += write(1, f_str->str + 1, percent - f_str->str - 1);
		f_str->str = percent;
	}
}

void	put_percent(t_fs *f_str)
{
	if (f_str->flags & MINUS)
	{
		f_str->ret += write (1, "%", 1);
		f_str->ret += print_spaces(f_str->width - 1);
	}
	else
		right_adjusted_percent(f_str);
	++f_str->str;
}
