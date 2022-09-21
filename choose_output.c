/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   choose_output.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 11:19:19 by jniemine          #+#    #+#             */
/*   Updated: 2022/09/21 20:03:11 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

void	choose_output_format(t_file_node *head, t_width *w, char **dir_paths)
{
	if (w && w->flags & PRINT_DIR_NAME)
	{	
		if (w->flags & PRINT_NL)
		{
			ft_printf("\n");
			w->flags ^= PRINT_NL;
		}
		ft_printf("%s:\n", w->dir_path);
	}
	if (!head)
		return ;
	if (w->flags & LONG_LST)
		print_long_format(head, *w, dir_paths);
	else
		print_columns(head, w, dir_paths);
}
