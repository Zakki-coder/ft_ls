/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 17:58:51 by jniemine          #+#    #+#             */
/*   Updated: 2022/08/15 16:21:55 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

void print_usage(void)
{
	ft_printf("usage: ls [%s] [file ...]\n", ALLOWED_OPTIONS);
	exit (-1);
}

int set_flags(char c, unsigned int *flags)
{
	if(c == 'l')
		*flags |= LONG_LST;
	else if(c == 'R')
		*flags |= RECURSIVE; 
	else if(c == 'r')
		*flags |= REVERSE_ORDER; 
	else if(c == 'a')
		*flags |= ALL; 
	else if(c == 't')
		*flags |= TIME_ORDER; 
	else if(c == '1')
		*flags |= ONE_COLUMN;
	else if(c == '@')
		*flags |= EXT_ATTR;
	else if(c == 'e')
		*flags |= ACL;
	else if(c == '-')
		return -1;
	else
	{
		ft_printf("ft_ls: illegal option -- %c\n", c);
		print_usage();
	}
	return (1);
}

//TODO Print illegal option and usage if illegal option.
int ls_get_flags(int argc, char **argv, unsigned int *flags)
{
	int		i;
	int		k;

	i = 1;
	while(i < argc && argv[i][0] == '-')
	{
		k = 0;
		while (argv[i][++k])
		{
			if(set_flags(argv[i][k], flags) < 0)
			{
				*flags |= PRINT_DIR_NAME;
				return (++i);
			}
		}
		++i;
	}
	return (i);
}


/*
void parser(int argc, char **argv, unsigned int flags)
{
	if(argc > 1)
	{
		return(get_flags(argc, argv);
	}
}
*/