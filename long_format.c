/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   long_format.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 19:31:18 by jniemine          #+#    #+#             */
/*   Updated: 2022/09/21 17:51:26 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

static void	six_months(char *output, char *timep, long long int time_difference)
{
	int	start;
	int	len;

	start = 0;
	len = 0;
	if (time_difference > (2629743 * 6)
		|| (-1 * time_difference) > (2629743 * 6))
	{
		while (timep[9 + start] && timep[9 + start] == ' ')
			++start;
		if (!timep[9 + 1])
			start = 0;
		while (timep[9 + start + len] && timep[9 + start + len] <= '9'
			&& timep[9 + start + len] >= '0')
			++len;
		ft_strncat(output, " ", 1);
		ft_strncat(output, timep + 9 + start, len);
	}
	else
		ft_strncat(output, timep, 5);
}

/*	On unix time, day is always 86400seconds.
	1 Month (30.44 days)	2629743 Seconds
*/
static void	print_time(t_file_node *node)
{
	char			*timep;
	time_t			current_time;
	char			output[27];
	long long int	time_difference;

	current_time = time(NULL);
	ft_bzero(output, 27);
	timep = ctime(&node->stat.st_mtimespec.tv_sec);
	if (!timep)
		error_exit();
	timep += 4;
	ft_strncpy(output, timep, 4);
	timep += 4;
	ft_strncat(output, timep, 3);
	timep += 3;
	time_difference = current_time - node->stat.st_mtimespec.tv_sec;
	six_months(output, timep, time_difference);
	ft_printf("%-*s", ft_strlen(output) + 1, output);
}

static void	choose_path_to_print(t_file_node *node, t_width *widths)
{
	char	link_buf[1024];

	ft_bzero((void *)link_buf, 1024);
	if (readlink(node->path, link_buf, 1024) > 0)
	{
		if (!(widths->is_file))
			ft_printf("%s -> %s\n", node->file_name, link_buf);
		else
			ft_printf("%s -> %s\n", node->path, link_buf);
	}
	else if (!(widths->is_file))
		ft_printf("%s\n", node->file_name);
	else
		ft_printf("%s\n", node->path);
}

static void	print_stat(t_file_node *h, t_width *widths, char **dpaths, int *i)
{
	char			*name;

	name = h->file_name;
	if (h->is_head)
		ft_printf("total %llu\n", widths->total_size);
	print_permissions(h->lstat.st_mode, h);
	ft_printf("%*u ", widths->link_col + 1, h->lstat.st_nlink);
	ft_printf("%-*s", widths->max_usr_col + 2, h->usr);
	ft_printf("%-*s", widths->max_grp_col + 1, h->grp);
	if (h->type == DT_BLK || h->type == DT_CHR)
		ft_printf("  %d,   %d ", h->d_major, h->d_minor);
	else
		ft_printf("%*d ", widths->size_col + 1, h->lstat.st_size);
	print_time(h);
	choose_path_to_print(h, widths);
	print_extended_attributes(h, widths->flags);
	if (dpaths && h->type & DT_DIR && ft_strcmp(name, ".") != 0
		&& ft_strcmp(name, "..") != 0)
		dpaths[(*i)++] = ft_strdup(h->path);
}

void	free_node(t_file_node **head)
{
	free((*head)->usr);
	free((*head)->grp);
	free((*head)->ext_attr);
	free((*head)->dir_path);
	free((*head)->file_name);
	free((*head)->path);
//	free(head);
}

void	print_long_format(t_file_node *head, t_width widths, char **dir_paths)
{
	int			i;
	t_file_node	*prev;

	i = 0;
	while (head)
	{
	//	while (head && !(widths.flags & ALL) && head->is_hidden)
	//	{
	//		head->is_head = 0;
	//		head = head->next;
	//		head->is_head = 1;
	//	}
		if (!head)
			break ;
		print_stat(head, &widths, dir_paths, &i);
		prev = head;
		head = head->next;
		free_node(&prev);
		free(prev);
	}
	return ;
}
