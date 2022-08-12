/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   choose_output.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 11:19:19 by jniemine          #+#    #+#             */
/*   Updated: 2022/08/12 13:58:55 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

void choose_output_format(t_file_node *head, t_width *widths, char **dir_paths)
{
	if (/*head && (widths->flags & RECURSIVE ||*/ widths->flags & PRINT_DIR_NAME)
		ft_printf("%s:\n", head->dir_path);
	while (head && !(widths->flags & ALL) && head->file_name[0] == '.')
	{
		head = head->next;
		head->is_head = 1;
	}
	if (!head)
		return;
	if (widths->flags & LONG_LST)
		print_loop(head, *widths, dir_paths);
	else
		print_columns(head, widths, dir_paths);
}