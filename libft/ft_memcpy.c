/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   beta_ft_memcpy.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 15:04:20 by jniemine          #+#    #+#             */
/*   Updated: 2021/11/23 18:08:44 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char	*dest_l;

	dest_l = (char *)dest;
	if (n > 0 && dest == NULL && src == NULL)
		return (dest);
	while (n--)
		*dest_l++ = *(char *)src++;
	return (dest);
}
