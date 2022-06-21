/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 19:10:41 by jniemine          #+#    #+#             */
/*   Updated: 2021/11/30 17:54:32 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int	count_delimiters(const char *s, char c)
{
	int	count;

	count = 0;
	while (*s)
	{
		if ((*s != c && *(s + 1) == c) || (*s != c && *(s + 1) == '\0'))
			++count;
		++s;
	}
	return (count);
}

static int	word(const char *s, char c)
{
	int	count;

	count = 0;
	while (*s != '\0' && *s != c)
	{
		++count;
		++s;
	}
	return (count);
}

static void	word_maker(const char *s, char ***res, char c)
{
	int	len;

	len = 0;
	len = word(s, c);
	**res = (char *)malloc(sizeof(char) * (len + 1));
	if (**res == NULL)
		return ;
	while (*s != c && *s != '\0')
		*(**res)++ = *s++;
	***res = '\0';
	**res -= len;
}

static char	**magic_machine(char **res, char const *s, char c)
{
	int		word_len;

	word_len = 0;
	while (*s)
	{
		if ((*s != c && *(s + 1) == c) || (*s != c && *(s + 1) == '\0'))
		{
			word_maker(s - word_len, &res, c);
			if (*(s + 1) == '\0')
				return (++res);
			s += 1;
			word_len = 0;
			if (*res == NULL)
				return (NULL);
			++res;
		}
		if (*s != c && *s != '\0')
			++word_len;
		++s;
	}
	return (res);
}

char	**ft_strsplit(char const *s, char c)
{
	int		n_delimit;
	char	**res;

	if (s == NULL)
		return (NULL);
	n_delimit = count_delimiters(s, c);
	res = (char **)malloc(sizeof(char *) * (n_delimit + 1));
	if (res == NULL)
	{	
		free(res);
		res = NULL;
		return (NULL);
	}
	res = magic_machine(res, s, c);
	if (res == NULL)
		ft_freeda((void ***)(&res), n_delimit);
	*(res) = NULL;
	return (res - (n_delimit));
}
