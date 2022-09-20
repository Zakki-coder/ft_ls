/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   column_output.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 00:13:14 by jniemine          #+#    #+#             */
/*   Updated: 2022/09/20 18:56:05 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

static int	count_tab_n(int longest_filename, int *word_width)
{
	const int	tab_stop = 8;
	int			tab_stop_n;

	tab_stop_n = 1;
	tab_stop_n = longest_filename / tab_stop;
	*word_width = tab_stop_n * tab_stop;
	if (*word_width % tab_stop == 0)
		*word_width += tab_stop;
	return (*word_width);
}

static int	count_rows(int file_n, int words_in_line)
{
	if (!words_in_line)
		return (1);
	while (file_n % words_in_line != 0)
		++file_n;
	return (file_n / words_in_line);
}

void	print_columns(t_file_node *head, t_width *widths, char **dir_paths)
{
	struct winsize	w;
	int				words_in_line_n;
	int				rows;
	int				word_width;

	word_width = 0;
	if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) < 0)
	{
		if (isatty(STDOUT_FILENO) == 0)
			widths->flags |= ONE_COLUMN;
		else
			error_exit();
	}
	widths->window_size = w;
	if (widths->flags & ONE_COLUMN)
		words_in_line_n = 1;
	else
		words_in_line_n = (w.ws_col)
			/ count_tab_n(widths->longest_filename, &word_width);
	rows = count_rows(widths->file_amount, words_in_line_n);
	head->flags = widths->flags;
	make_columns(head, rows, word_width, dir_paths);
}
