/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 15:32:53 by jniemine          #+#    #+#             */
/*   Updated: 2021/11/23 22:50:21 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_strcmp(const char *s1, const char *s2)
{
	const unsigned char	*l_s1 = (const unsigned char *)s1;
	const unsigned char	*l_s2 = (const unsigned char *)s2;

	while (*l_s1 == *l_s2 && *s1 != '\0' && *l_s2 != '\0')
	{
		++l_s1;
		++l_s2;
	}
	return (*l_s1 - *l_s2);
}
