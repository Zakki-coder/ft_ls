/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_list_part2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 00:07:53 by jniemine          #+#    #+#             */
/*   Updated: 2022/09/15 00:08:45 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

void	handle_path(char *root_path, t_file_node *head, t_dir *filep, int flags)
{
	int	len;

	len = ft_strlen(root_path) + ft_strlen(filep->d_name) + 2;
	head->path = ft_memalloc(len);
	head->dir_path = ft_memalloc(ft_strlen(root_path) + 1);
	if (!head->path || !head->dir_path)
		error_exit();
	ft_strcpy(head->dir_path, root_path);
	if ((flags & RECURSIVE || flags & ONE_COLUMN)
		&& ft_strncmp(root_path, "./", 2) == 0)
		root_path += 2;
	if (ft_strcmp(root_path, ".") != 0)
		ft_strcat(head->path, root_path);
	if (ft_strlen(head->path) > 0
		&& head->path[ft_strlen(head->path) - 1] != '/')
		ft_strcat(head->path, "/");
	ft_strcat(head->path, filep->d_name);
	if (filep->d_name[0] == '.')
		head->is_hidden = 1;
}

void	get_t_dir_info(t_dir *filep, t_file_node *node)
{
	if (!filep)
		return ;
	node->file_name = (char *)ft_memalloc(sizeof(char) * filep->d_namlen + 1);
	if (!node->file_name)
		error_exit();
	ft_strcpy(node->file_name, filep->d_name);
}

void	get_stat_info(t_file_node *node)
{
	struct passwd	*pw;
	struct group	*grp;

	if (lstat(node->path, &node->stat) < 0
		|| lstat(node->path, &node->lstat) < 0)
		error_exit();
	pw = getpwuid(node->lstat.st_uid);
	grp = getgrgid(node->lstat.st_gid);
	if (!pw || !grp)
		error_exit();
	node->usr = ft_strdup(pw->pw_name);
	node->grp = ft_strdup(grp->gr_name);
	if (!node->usr || !node->grp)
		error_exit();
	node->d_minor = minor(node->stat.st_rdev);
	node->d_major = major(node->stat.st_rdev);
}

static void	update_width_split(t_width *widths)
{
	if (!widths->dir_path)
		error_exit();
}

void	update_widths(t_file_node *head, t_width *widths)
{
	unsigned int	len;

	if (((widths->flags & ALL))
		|| (!head->is_hidden && !(widths->flags & ALL)))
	{
		++widths->file_amount;
		if (head->type & DT_DIR)
			widths->dir_amount++;
		len = ft_strlen(head->file_name);
		if (widths->longest_filename < len)
			widths->longest_filename = len;
		if (widths->link_col < nb_len(head->lstat.st_nlink))
			widths->link_col = nb_len(head->lstat.st_nlink);
		if (widths->size_col < nb_len(head->lstat.st_size))
			widths->size_col = nb_len(head->lstat.st_size);
		len = ft_strlen(head->usr);
		if (widths->max_usr_col < len)
			widths->max_usr_col = len;
		len = ft_strlen(head->grp);
		if (widths->max_grp_col < len)
			widths->max_grp_col = len;
		widths->total_size += head->stat.st_blocks;
	}
	widths->dir_path = ft_strdup(head->dir_path);
	update_width_split(widths);
}
