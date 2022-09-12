/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_list_part2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 20:22:48 by jniemine          #+#    #+#             */
/*   Updated: 2022/09/12 20:24:41 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

static void	free_everything(char **root_paths, t_file_node *head)
{
	int	i;

	i = 0;
	free_lst(head);
	while (root_paths[i])
		free(root_paths[i++]);
}

static void	print_file_list(t_file_node *lst_start, t_width *widths)
{
	lst_start = sort(&lst_start, widths->flags, widths);
	lst_start->is_head = 0;
	if (widths->flags & LONG_LST)
		print_loop(lst_start, *widths, NULL);
	else
		print_columns(lst_start, widths, NULL);
}

/* Remember to free filepointers */
void	create_file_list(t_dir **fileps, t_width *widths, char **root_paths)
{
	t_file_node	*head;
	t_file_node	*lst_start;
	t_dir		*filep;

	head = create_node();
	lst_start = head;
	while (*fileps != NULL)
	{
		filep = *fileps;
		get_t_dir_info(filep, head);
		handle_path(*root_paths++, head, filep, widths->flags);
		get_stat_info(head);
		head->type = filep->d_type;
		head->flags = widths->flags;
		update_widths(head, widths);
		widths->is_file = 1;
		if (*(++fileps) != NULL)
		{
			head->next = create_node();
			head = head->next;
		}
	}
	print_file_list(lst_start, widths);
	free_everything(root_paths, lst_start);
}
