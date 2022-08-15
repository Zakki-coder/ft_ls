/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   choose_output.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 11:19:19 by jniemine          #+#    #+#             */
/*   Updated: 2022/08/15 22:40:56 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

/* CHANGELOG: Changed dir_path to widths Shouldnt it has alla the dir info and node the file info?*/
void choose_output_format(t_file_node *head, t_width *widths, char **dir_paths)
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
//	while (head != NULL && !(widths->flags & ALL) && head->file_name[0] == '.')
//	{
//		head = head->next;
//		if (head)
//			head->is_head = 1;
//	}
	if (!head)
		return;
	if (widths->flags & LONG_LST)
		print_loop(head, *widths, dir_paths);
	else
		print_columns(head, widths, dir_paths);
}