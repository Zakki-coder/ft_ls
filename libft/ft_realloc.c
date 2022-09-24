/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 17:13:41 by jniemine          #+#    #+#             */
/*   Updated: 2022/01/13 21:22:25 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	*ft_realloc(void *old_ptr, size_t old_size, size_t new_size)
{
	void	*new_ptr;

	if (old_ptr == NULL)
	{
		new_ptr = (void *)ft_memalloc(new_size);
		return (new_ptr);
	}
	if (old_size == 0)
	{
		new_ptr = (void *)ft_memalloc(new_size);
		free(old_ptr);
		old_ptr = NULL;
		return (new_ptr);
	}
	new_ptr = (void *)ft_memalloc(new_size);
	if (new_ptr == NULL)
		return (NULL);
	ft_memcpy(new_ptr, old_ptr, old_size);
	free(old_ptr);
	old_ptr = NULL;
	return (new_ptr);
}
