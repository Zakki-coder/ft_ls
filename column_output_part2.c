/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   column_output_part2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 21:12:00 by jniemine          #+#    #+#             */
/*   Updated: 2022/09/24 02:49:22 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

static void	column_output(t_list **columns, int word_width)
{
	int		i;
	t_list	*prev;

	i = 0;
	while (columns[i])
	{
		while (columns[i])
		{
			ft_printf("%-*s", word_width, (char *)columns[i]->content);
			prev = columns[i];
			columns[i] = columns[i]->next;
			free(prev->content);
			free(prev);
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

	if (!alst)
		return ;
	new = ft_lstnew(content, ft_strlen(content) + 1);
	if (!new)
		return ;
	while (alst->next)
		alst = alst->next;
	alst->next = new;
}

void	make_columns(t_file_node *head, int rows, int word_width, char **dirs)
{
	t_list		**columns;
	t_file_node	*prev;
	int			i;
	int			j;
	int			flags;

	flags = head->flags;
	columns = init_helper(&i, &j, rows);
	while (head)
	{
		ft_lstappend(columns[i % rows], head->file_name);
		if (!columns[i % rows])
			columns[i % rows] = ft_lstnew(head->file_name,
					ft_strlen(head->file_name) + 1);
		++i;
		if (dirs && head->type == DT_DIR && ft_strcmp(head->file_name, ".") != 0
			&& ft_strcmp(head->file_name, "..") != 0)
			dirs[j++] = ft_strdup(head->path);
		prev = head;
		head = head->next;
		free_node(&prev);
		free(prev);
	}
	column_output(columns, word_width);
	free(columns);
}
