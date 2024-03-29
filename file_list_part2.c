/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_list_part2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 20:22:48 by jniemine          #+#    #+#             */
/*   Updated: 2022/09/24 18:30:50 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

static void	free_everything(char **root_paths)
{
	int	i;

	i = 0;
	while (root_paths[i])
		free(root_paths[i++]);
}

static void	print_file_list(t_file_node *lst_start, t_width *widths)
{
	lst_start = sort(&lst_start, widths->flags, widths);
	lst_start->is_head = 0;
	if (widths->flags & LONG_LST)
		print_long_format(lst_start, *widths, NULL);
	else
		print_columns(lst_start, widths, NULL);
}

void	create_file_list(t_dir **fileps, t_width *widths, char **root_paths)
{
	t_file_node	*head;
	t_file_node	*lst_start;

	head = create_node();
	lst_start = head;
	while (*fileps != NULL)
	{
		get_t_dir_info(*fileps, head);
		handle_path(*root_paths, head, *fileps, widths->flags);
		free(*root_paths++);
		get_stat_info(head);
		head->type = (*fileps)->d_type;
		head->flags = widths->flags;
		update_widths(head, widths);
		widths->is_file = 1;
		free(*fileps);
		if (*(++fileps) != NULL)
		{
			head->next = create_node();
			head = head->next;
		}
	}
	print_file_list(lst_start, widths);
	free_everything(root_paths);
}
