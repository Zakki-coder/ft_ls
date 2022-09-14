/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   column_output_part2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 21:12:00 by jniemine          #+#    #+#             */
/*   Updated: 2022/09/14 23:52:30 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

static void	column_output(t_list **columns, int word_width)
{
	int	i;

	i = 0;
	while (columns[i])
	{
		while (columns[i])
		{
			ft_printf("%-*s", word_width, (char *)columns[i]->content);
			columns[i] = columns[i]->next;
		}
		ft_printf("\n");
		++i;
	}
}

static t_list	**init_helper(int *i, int *j, int rows)
{
	t_list	**columns;

	*i = 0;
	*j = 0;
	columns = (t_list **)ft_memalloc(sizeof(t_list *) * (rows + 1));
	return (columns);
}

static void	ft_lstappend(t_list *alst, char *content)
{
	t_list	*new;

	new = ft_lstnew(content, ft_strlen(content) + 1);
	if (!alst || !new)
		return ;
	while (alst->next)
		alst = alst->next;
	alst->next = new;
}

static int	pass_hidden(t_file_node **h, int flags)
{
	if ((*h)->is_hidden && !(flags & ALL))
	{
		(*h) = (*h)->next;
		return (1);
	}
	return (0);
}

/* Lexicographical ordering uses strcmp so files
	starting with capital letter come before */
void	make_columns(t_file_node *h, int rows, int word_width, char **dirs)
{
	t_list		**cols;
	int			i;
	int			j;
	int			flags;

	flags = h->flags;
	cols = init_helper(&i, &j, rows);
	while (h)
	{
		if (pass_hidden(&h, flags))
			continue ;
		ft_lstappend(cols[i % rows], h->file_name);
		if (!cols[i % rows] && (flags & ONE_COLUMN))
			cols[i++ % rows] = ft_lstnew(h->file_name,
					ft_strlen(h->file_name) + 1);
		else if (!cols[i % rows])
			cols[i++ % rows] = ft_lstnew(h->file_name,
					ft_strlen(h->file_name) + 1);
		if (dirs && h->type & DT_DIR && ft_strcmp(h->file_name, ".") != 0
			&& ft_strcmp(h->file_name, "..") != 0)
			dirs[j++] = h->path;
		h = h->next;
	}
	column_output(cols, word_width);
}
