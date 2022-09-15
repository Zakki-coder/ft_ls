/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 14:44:27 by jniemine          #+#    #+#             */
/*   Updated: 2022/09/15 19:50:12 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

static void	init_helper(t_file_node **prev, t_width *widths,
		t_file_node **head, t_file_node **lst_start)
{
	int	flags;

	*prev = NULL;
	flags = widths->flags;
	ft_bzero((void *)widths, sizeof(*widths));
	widths->flags = flags;
	*head = create_node();
	if (!(*head))
		error_exit();
	*lst_start = *head;
}

static void	advance_head(t_file_node **head, t_file_node **prev)
{
	(*head)->next = create_node();
	*prev = *head;
	*head = (*head)->next;
}

t_file_node	*create_list(DIR *dirp, char *path, t_width *widths)
{
	t_dir		*filep;
	t_file_node	*head;
	t_file_node	*prev;
	t_file_node	*lst_start;

	filep = read_stream(dirp);
	if (!filep)
		return (NULL);
	init_helper(&prev, widths, &head, &lst_start);
	while (filep != NULL && dirp != NULL)
	{
		get_t_dir_info(filep, head);
		handle_path(path, head, filep, widths->flags);
		get_stat_info(head);
		head->type = filep->d_type;
		update_widths(head, widths);
		filep = read_stream(dirp);
		if (filep != NULL)
			advance_head(&head, &prev);
	}
	if (!filep && errno != 0)
		error_exit();
	return (sort(&lst_start, widths->flags, widths));
}
