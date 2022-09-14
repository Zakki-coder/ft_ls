/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 14:44:27 by jniemine          #+#    #+#             */
/*   Updated: 2022/09/14 20:41:54 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

t_file_node	*create_node(void)
{
	t_file_node	*new;

	new = (t_file_node *)ft_memalloc(sizeof(t_file_node));
	if (!new)
		error_exit();
	ft_bzero(new, sizeof(*new));
	new->is_head = 0;
	new->total_blocks = 0;
	new->ext_attr = NULL;
	new->path = NULL;
	new->next = NULL;
	return (new);
}

void	print_loop(t_file_node *head, t_width widths, char **dir_paths)
{
	int	i;

	i = 0;
	while (head)
	{
		while (head && !(widths.flags & ALL) && head->is_hidden)
		{
			head->is_head = 0;
			head = head->next;
			head->is_head = 1;
		}
		if (!head)
			break ;
		print_stat(head, &widths, dir_paths, &i);
		head = head->next;
	}
	return ;
}

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

/* Get user and group info also */
/* Get device minor and major also */
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

static void update_width_split(t_width *widths)
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

static void	init_helper(t_file_node **prev, t_width *widths,
		t_file_node **head, t_file_node **lst_start)
{
	int	flags;

	*prev = NULL;
	flags = widths->flags;
	ft_bzero((void *)widths, sizeof(*widths));
	widths->flags = flags;
	*head = create_node();
	if (!(*head))
		error_exit();
	*lst_start = *head;
}

static void advance_head(t_file_node **head, t_file_node **prev)
{
	(*head)->next = create_node();
	*prev = *head;
	*head = (*head)->next;
}

/* This reads files from one directory at a time */
t_file_node	*create_list(DIR *dirp, char *path, t_width *widths)
{
	t_dir		*filep;
	t_file_node	*head;
	t_file_node	*prev;
	t_file_node	*lst_start;

	filep = read_stream(dirp);
	if (!filep)
		return (NULL);
	init_helper(&prev, widths, &head, &lst_start);
	while (filep != NULL && dirp != NULL)
	{
		get_t_dir_info(filep, head);
		handle_path(path, head, filep, widths->flags);
		get_stat_info(head);
		head->type = filep->d_type;
		update_widths(head, widths);
		filep = read_stream(dirp);
		if (filep != NULL)
			advance_head(&head, &prev);
	}
	if (!filep && errno != 0)
		error_exit();
	return (sort(&lst_start, widths->flags, widths));
}
