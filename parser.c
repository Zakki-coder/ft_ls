/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 17:58:51 by jniemine          #+#    #+#             */
/*   Updated: 2022/09/23 14:19:16 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

static void	print_usage(void)
{
	const char	*usage = "usage: ft_ls [-lRrat1] [file ...]\n";

	write(2, usage, ft_strlen(usage));
	exit (1);
}

static void	print_flag_errors(char c)
{
	write(STDERR_FILENO, "ft_ls: illegal option -- ", 25);
	write(STDERR_FILENO, &c, 1);
	write(STDERR_FILENO, "\n", 1);
	print_usage();
}

static int	set_flags(char c, unsigned int *flags)
{
	if (c == 'l')
	{
		if (*flags & ONE_COLUMN)
			*flags ^= ONE_COLUMN;
		*flags |= LONG_LST;
	}
	else if (c == 'R')
		*flags |= RECURSIVE;
	else if (c == 'r')
		*flags |= REVERSE_ORDER;
	else if (c == 'a')
		*flags |= ALL;
	else if (c == 't')
		*flags |= TIME_ORDER;
	else if (c == '1')
	{
		if (*flags & LONG_LST)
			*flags ^= LONG_LST;
		*flags |= ONE_COLUMN;
	}
	else if (c == '@')
		*flags |= EXT_ATTR;
	else
		print_flag_errors(c);
	return (1);
}

int	ls_get_flags(int argc, char **argv, unsigned int *flags)
{
	int		i;
	int		k;

	i = 1;
	while (i < argc && argv[i][0] == '-')
	{
		k = 0;
		if (argv[i][1] == '\0' || argv[i][1] == ' ')
			return (i);
		if (argv[i][1] == '-' && ft_strlen(argv[i]) == 2)
			return (++i);
		while (argv[i][++k])
			set_flags(argv[i][k], flags);
		++i;
	}
	return (i);
}
