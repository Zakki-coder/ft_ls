/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 17:58:51 by jniemine          #+#    #+#             */
/*   Updated: 2022/07/12 00:27:52 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

void print_usage(void)
{
	ft_printf("usage: ls [%s] [file ...]\n", ALLOWED_OPTIONS);
	exit (-1);
}

void set_flags(char c, unsigned int *flags)
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
	else
	{
		ft_printf("ft_ls: illegal option -- %c\n", c);
		print_usage();
	}
}

//TODO Print illegal option and usage if illegal option.
int ls_get_flags(int argc, char **argv, unsigned int *flags)
{
	int		i;
	int		k;

	i = 1;
	k = 0;
	while(i < argc && argv[i][0] == '-')
	{
		while (argv[i][++k])
			set_flags(argv[i][k], flags);
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