/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 14:44:27 by jniemine          #+#    #+#             */
/*   Updated: 2022/09/24 03:54:25 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

static void	init_helper(char *path, t_width *widths,
		t_file_node **head, t_file_node **lst_start)
{
	int	flags;

	flags = widths->flags;
	ft_bzero((void *)widths, sizeof(*widths));
	widths->dir_path = ft_strdup(path);
	widths->flags = flags;
	*head = create_node();
	if (!(*head))
		error_exit();
	*lst_start = *head;
}

/* Skip hidden files if they are not asked for */
static void	skip_hidden(t_file_node **h, t_width *w, DIR *dirp, t_dir **filep)
{
	if (read_stream(dirp, filep) && *filep != NULL)
	{
		if ((*h)->file_name && (w->flags & ALL
				|| (!(w->flags & ALL) && !((*filep)->d_name[0] == '.'))))
		{
			(*h)->next = create_node();
			*h = (*h)->next;
		}
	}
}

static void	last_checks(t_file_node **lst_start, t_dir *filep)
{
	if (!(*lst_start)->file_name)
	{
		free(*lst_start);
		*lst_start = NULL;
	}
	if (!filep && errno != 0)
		error_exit();
}

static int	get_stat_wrap(t_file_node **head)
{
	if (get_stat_info(*head))
	{
		free_node(head);
		free(*head);
		return (1);
	}
	return (0);
}

t_file_node	*create_list(DIR *dirp, char *path, t_width *widths)
{
	t_dir		*filep;
	t_file_node	*head;
	t_file_node	*lst_start;

	read_stream(dirp, &filep);
	if (!filep)
		return (NULL);
	init_helper(path, widths, &head, &lst_start);
	while (filep != NULL && dirp != NULL)
	{
		if (widths->flags & ALL
			|| (!(widths->flags & ALL) && !(filep->d_name[0] == '.')))
		{
			get_t_dir_info(filep, head);
			handle_path(path, head, filep, widths->flags);
			if (get_stat_wrap(&head))
				return (NULL);
			head->type = filep->d_type;
			update_widths(head, widths);
		}
		skip_hidden(&head, widths, dirp, &filep);
	}
	last_checks(&lst_start, filep);
	return (sort(&lst_start, widths->flags, widths));
}
