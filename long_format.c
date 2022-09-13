/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   long_format.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 19:31:18 by jniemine          #+#    #+#             */
/*   Updated: 2022/09/13 19:16:43 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

void	six_months(char *output, char *timep, long long int time_difference)
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
void	print_time(t_file_node *node)
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

void	print_stat(t_file_node *node, t_width *widths, char **dir_paths, int *i)
{
	char			*name;

	name = node->file_name;
	if (node->is_head)
		ft_printf("total %llu\n", widths->total_size);
	print_permissions(node->lstat.st_mode, node);
	ft_printf("%*u ", widths->link_col + 1, node->lstat.st_nlink);
	ft_printf("%-*s", widths->max_usr_col + 2, node->usr);
	ft_printf("%-*s", widths->max_grp_col + 1, node->grp);
	if (node->type == DT_BLK || node->type == DT_CHR)
		ft_printf("  %d,   %d ", node->d_major, node->d_minor);
	else
		ft_printf("%*d ", widths->size_col + 1, node->lstat.st_size);
	print_time(node);
	choose_path_to_print(node, widths);
	print_extended_attributes(node, widths->flags);
	if (dir_paths && node->type & DT_DIR && ft_strcmp(name, ".") != 0
		&& ft_strcmp(name, "..") != 0)
		dir_paths[(*i)++] = node->path;
}
