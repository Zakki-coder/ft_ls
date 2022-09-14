/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_extended_attributes.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 20:00:45 by jniemine          #+#    #+#             */
/*   Updated: 2022/09/14 19:32:57 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

void	print_extended_attributes(t_file_node *head, int flags)
{
	int			i;
	int			tab_n;
	int			print_len;

	i = 0;
	if (flags & EXT_ATTR && head->ext_attr != NULL)
	{
		while (i < head->ext_attr_len)
		{
			print_len = getxattr(head->path, head->ext_attr + i,
					NULL, 0, 0, XATTR_NOFOLLOW);
			tab_n = ft_strlen(head->ext_attr + i) / 8;
			ft_printf("\t%s", head->ext_attr + i);
			ft_printf("%*ld\n", 13 + tab_n * 8
				- ft_strlen(head->ext_attr + i), print_len);
			i += ft_strlen(head->ext_attr + i) + 1;
		}
	}
}
