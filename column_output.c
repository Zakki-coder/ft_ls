/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   column_output.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 00:13:14 by jniemine          #+#    #+#             */
/*   Updated: 2022/07/20 10:53:45 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

static int count_tab_n(int longest_filename, int *word_width)
{
	const	int tab_stop = 8;
	int		tab_stop_n;

	tab_stop_n = 0;
	while (longest_filename)
	{
		longest_filename /= tab_stop;
		++tab_stop_n;
	}
	*word_width = tab_stop_n * tab_stop;
	return (*word_width);
}

void ft_lstappend(t_list *alst, t_list *new)
{
	if (!alst || !new)
		return ;
	while (alst->next)
		alst = alst->next;
	alst->next = new;
}

void make_columns(t_file_node *head/*, int words_in_line_n*/, int rows, int word_width)
{
	t_list		**columns;
//	int			word_count;
//	t_file_node *head_start;
	int			i;

//	word_count = 0;
	i = 0;
//	head_start = head;
	columns = (t_list **)ft_memalloc(sizeof(t_list *) * (rows + 1));
	/* First get directories */
	while (head)
	{
		ft_lstappend(columns[i % rows], ft_lstnew(head->file_name, ft_strlen(head->file_name)));
		if (!columns[i % rows])
			columns[i % rows] = ft_lstnew(head->file_name, ft_strlen(head->file_name));
		++i;
		head = head->next;
	}
	/*Debbuger*/
	i = 0;
	while (columns[i])
	{
		while (columns[i])
		{
			ft_printf("%-*s", word_width, (char *)columns[i]->content);
			columns[i] = columns[i]->next;
		}
		printf("\n");
		++i;
	}
}
void print_columns(t_file_node *head, t_width *widths)
{
    struct	winsize w;
	int		words_in_line_n;
	int		rows;
//	int		word_count;
	int		word_width;

//	word_count = 0;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	widths->window_size = w;
	//We need to leave one empty column with width of word_width.
	words_in_line_n = (w.ws_col) / count_tab_n(widths->longest_filename, &word_width);
	if (words_in_line_n > 1)
		words_in_line_n -= 1;
	rows = widths->file_amount / words_in_line_n;
	make_columns(head/*, words_in_line*/, rows, word_width);
	/*
	while (head)
	{
		++word_count;
		ft_printf("%-*s", word_width, head->file_name);
		if ((word_count % words_in_line_n) == 0)
			ft_printf("\n");
		head = head->next;
	}
	*/
//	printf("file amount: %d\n", widths->file_amount);
//	printf("Word Width: %d\n", word_width);
//	printf("longest filename:%d\n", widths->longest_filename);
//    printf ("lines %d words_in_line: %d\n", w.ws_row, words_in_line_n);
//    printf ("columns %d rows: %d\n", w.ws_col, rows);
}
//First print directories, then filenames.
//TODO get terminal tabsize for columns.
//Find longest filename, add blanks.
//Calculate how many of those can fit in one line
//print accordingly.
