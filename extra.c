/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 03:53:06 by jniemine          #+#    #+#             */
/*   Updated: 2022/09/24 03:53:34 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

t_file_node	*create_node(void)
{
	t_file_node	*new;

	new = (t_file_node *)ft_memalloc(sizeof(t_file_node));
	if (!new)
		error_exit();
	ft_bzero(new, sizeof(*new));
	new->is_head = 0;
	new->total_blocks = 0;
	new->ext_attr = NULL;
	new->path = NULL;
	new->next = NULL;
	return (new);
}
