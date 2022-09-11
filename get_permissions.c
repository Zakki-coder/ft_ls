/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_permissions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 17:40:07 by jniemine          #+#    #+#             */
/*   Updated: 2022/09/11 17:59:49 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

static void	get_extended_permissions(t_file_node *head, char *permissions)
{
	ssize_t	size;
	acl_t	acl;

	size = listxattr(head->path, NULL, 0, XATTR_NOFOLLOW);
	acl = acl_get_link_np(head->path, ACL_TYPE_EXTENDED);
	if (size > 0)
	{
		head->ext_attr_len = size;
		if (permissions != NULL)
			permissions[10] = '@';
		head->ext_attr = (char *)ft_memalloc(size + 1);
		listxattr(head->path, head->ext_attr, size, 0);
	}
	else if (acl)
	{
		head->acl = acl;
		if (permissions != NULL)
			permissions[10] = '+';
	}
	else if (permissions != NULL)
		permissions[10] = ' ';
	permissions[11] = '\0';
	ft_printf("%-11s", permissions);
}

static void	third_field(unsigned int st_mode, char *permissions, int i)
{
	if ((!(st_mode & S_IXUSR) && st_mode & S_ISUID && i == 3)
		|| (!(st_mode & S_IXGRP) && st_mode & S_ISGID && i == 6))
		*permissions = 'S';
	else if ((st_mode & S_IXUSR && st_mode & S_ISUID && i == 3)
		|| (st_mode & S_IXGRP && st_mode & S_ISGID && i == 6))
		*permissions = 's';
	else if ((st_mode & S_IXUSR && i == 3)
		|| (st_mode & S_IXGRP && i == 6)
		|| (st_mode & S_IXOTH && i == 9))
		*permissions = 'x';
}

static void	get_file_type(t_file_node *node, char *permissions)
{
	unsigned int	type;

	type = node->type;
	if (type == DT_DIR)
		permissions[0] = 'd';
	else if (type == DT_LNK)
		permissions[0] = 'l';
	else if (type == DT_BLK)
		permissions[0] = 'b';
	else if (type == DT_CHR)
		permissions[0] = 'c';
	else if (type == DT_SOCK)
		permissions[0] = 's';
	else if (type == DT_FIFO)
		permissions[0] = 'p';
}

void	print_permissions(unsigned int st_mode, t_file_node *node)
{
	char	permissions[12];

	ft_memset(permissions, '-', 10);
	get_file_type(node, permissions);
	if (st_mode & S_IRUSR)
		permissions[1] = 'r';
	if (st_mode & S_IWUSR)
		permissions[2] = 'w';
	third_field(st_mode, &permissions[3], 3);
	if (st_mode & S_IRGRP)
		permissions[4] = 'r';
	if (st_mode & S_IWGRP)
		permissions[5] = 'w';
	third_field(st_mode, &permissions[6], 6);
	if (st_mode & S_IROTH)
		permissions[7] = 'r';
	if (st_mode & S_IWOTH)
		permissions[8] = 'w';
	if (!(st_mode & S_IXUSR) && st_mode & S_ISVTX)
		permissions[9] = 'T';
	else if (st_mode & S_IXUSR && st_mode & S_ISVTX)
		permissions[9] = 't';
	else
		third_field(st_mode, &permissions[9], 9);
	get_extended_permissions(node, permissions);
}
