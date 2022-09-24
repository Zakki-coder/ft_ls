/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_freeda.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 17:36:12 by jniemine          #+#    #+#             */
/*   Updated: 2022/09/24 18:18:49 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	ft_freeda(void ***a, size_t row)
{
	unsigned int	i;

	i = 0;
	while (i < row)
	{
		free(*((*a) + i));
		*((*a) + i) = NULL;
		++i;
	}
	free(*a);
	*a = NULL;
}
	/* 
	 * Takes the address of double pointer as param a
	 * and number of sub pointers as param row frees all and sets them to NULL
	 */
