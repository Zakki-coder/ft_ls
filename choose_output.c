/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   choose_output.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 11:19:19 by jniemine          #+#    #+#             */
/*   Updated: 2022/09/14 19:50:12 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

void	choose_output_format(t_file_node *head, t_width *widths, char **dpaths)
{
	if (widths && widths->flags & PRINT_DIR_NAME)
	{	
		if (widths->flags & PRINT_NL)
		{
			ft_printf("\n");
			widths->flags ^= PRINT_NL;
		}
		ft_printf("%s:\n", widths->dir_path);
	}
	if (!head)
		return ;
	if (widths->flags & LONG_LST)
		print_loop(head, *widths, dpaths);
	else
		print_columns(head, widths, dpaths);
}
