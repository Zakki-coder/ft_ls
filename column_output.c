/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   column_output.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 00:13:14 by jniemine          #+#    #+#             */
/*   Updated: 2022/08/09 17:13:17 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

static int count_tab_n(int longest_filename, int *word_width)
{
	const int	tab_stop = 8;
	int			tab_stop_n;

	tab_stop_n = 1;
	/*
	while (longest_filename)
	{
		longest_filename /= tab_stop;
		printf("longest: %d\n", longest_filename);
		++tab_stop_n;
	}
	*/	
	tab_stop_n = longest_filename / tab_stop;
	*word_width = tab_stop_n * tab_stop;
	if (*word_width % tab_stop == 0)
		*word_width += tab_stop;
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

/* Lexicographical ordering uses strcmp so files starting with capital letter come before */
void make_columns(t_file_node *head, int rows, int word_width, char **dir_paths)
{
	t_list		**columns;
//	int			word_count;
//	t_file_node *head_start;
	int			i;
	int			j;

//	word_count = 0;
	i = 0;
	j = 0;
//	head_start = head;
	columns = (t_list **)ft_memalloc(sizeof(t_list *) * (rows + 1));
	/* First get directories */
	while (head)
	{
		ft_lstappend(columns[i % rows], ft_lstnew(head->file_name, ft_strlen(head->file_name) + 1));
		if (!columns[i % rows])
			columns[i % rows] = ft_lstnew(head->file_name, ft_strlen(head->file_name) + 1);
		++i;
		if (dir_paths && head->type & DT_DIR && ft_strcmp(head->file_name, ".") != 0 && ft_strcmp(head->file_name, "..") != 0)
			dir_paths[j++] = head->path;
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
		ft_printf("\n");
		++i;
	}
}

int count_rows(int file_n, int words_in_line)
{
	while (file_n % words_in_line != 0)
		++file_n;
	return (file_n / words_in_line);
}

/* If possible, leave one empty column. */
void print_columns(t_file_node *head, t_width *widths, char **dir_paths)
{
    struct	winsize w;
	int		words_in_line_n;
	int		rows;
	int		word_width;

    if(ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) < 0)
		error_exit();
	widths->window_size = w;
	if (widths->flags & ONE_COLUMN)
		words_in_line_n = 1;
	else
		words_in_line_n = (w.ws_col) / count_tab_n(widths->longest_filename, &word_width);
	rows = count_rows(widths->file_amount, words_in_line_n);
	make_columns(head, rows, word_width, dir_paths);
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
