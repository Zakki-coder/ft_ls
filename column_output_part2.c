/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   column_output_part2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 21:12:00 by jniemine          #+#    #+#             */
/*   Updated: 2022/09/12 18:08:09 by jniemine         ###   ########.fr       */
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

/* Lexicographical ordering uses strcmp so files
	starting with capital letter come before */
void	make_columns(t_file_node *head, int rows, int word_width, char **dirs)
{
	t_list		**columns;
	int			i;
	int			j;

	columns = init_helper(&i, &j, rows);
	while (head)
	{
		if (head->flags & ONE_COLUMN)
			ft_lstappend(columns[i % rows], head->path);
		else
			ft_lstappend(columns[i % rows], head->file_name);
		if (!columns[i % rows] && head->flags & ONE_COLUMN)
			columns[i % rows] = ft_lstnew(head->path,
					ft_strlen(head->path) + 1);
		else if (!columns[i % rows])
			columns[i % rows] = ft_lstnew(head->file_name,
					ft_strlen(head->file_name) + 1);
		++i;
		if (dirs && head->type & DT_DIR && ft_strcmp(head->file_name, ".") != 0
			&& ft_strcmp(head->file_name, "..") != 0)
			dirs[j++] = head->path;
		head = head->next;
	}
	column_output(columns, word_width);
}
