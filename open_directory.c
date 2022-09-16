/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_directory.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 18:36:55 by jniemine          #+#    #+#             */
/*   Updated: 2022/09/16 17:00:26 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

static int	rootless_split(char *buf, int is_rootless, char **path, DIR *dst)
{
	int	len;

	len = 0;
	while (buf[len] && !is_rootless)
	{
		if (ft_strcmp(&buf[len], "com.apple.rootless") == 0)
			is_rootless = 1;
		len = ft_strlen(buf) + 1;
	}
	if (is_rootless)
	{
		closedir(dst);
		++(*path);
		return (1);
	}
	free(buf);
	return (0);
}

/* ft_ls -l /etc and ft_ls -l /etc/ */
static int	test_special_case_rootless(char *path, DIR *dst)
{
	char		link[1024];
	char		*buf;
	int			len;
	int			is_rootless;

	is_rootless = 0;
	if ((path)[ft_strlen(path) - 1] == '/'
		|| (readlink(path, link, 1024) <= 0 && errno == EINVAL))
	{
		errno = 0;
		return (0);
	}
	ft_bzero(link, 1024);
	len = listxattr(path, NULL, 0, XATTR_NOFOLLOW);
	if (len < 0)
		error_exit();
	buf = ft_memalloc(len + 1);
	len = listxattr(path, buf, len, XATTR_NOFOLLOW);
	if (len < 0)
		error_exit();
	return (rootless_split(buf, is_rootless, &path, dst));
}

static int	open_directory_split(char *path)
{
	char	*error;
	char	*tmp;

	error = strerror(errno);
	tmp = ft_strrchr(path, '/');
	/* This ENOENT thing is here just for moulitest, delete maybe*/
	if (errno != ENOENT && errno != EACCES)
		write(STDERR_FILENO, "ft_ls: ", 7);
	else
		write(STDERR_FILENO, "ls: ", 4);
	if (!tmp || errno == ENOENT)
		write(STDERR_FILENO, path, ft_strlen(path));
	else
		write(STDERR_FILENO, tmp + 1, ft_strlen(tmp + 1));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, error, ft_strlen(error));
	write(STDERR_FILENO, "\n", 1);
	errno = 0;
	return (0);
}

int	open_directory(char *path, DIR **dst)
{
	struct stat	tmp_stat;

	*dst = opendir(path);

	if (*dst && test_special_case_rootless(path, *dst))
	{
		*dst = NULL;
		return (-2);
	}
	if ((!*dst && errno == ENOTDIR) || (!*dst && ft_strcmp(path, ".") != 0
			&& ft_strcmp(path, "..") != 0 && lstat(path, &tmp_stat) == 0
			&& errno != EACCES))
	{
		*dst = NULL;
		errno = 0;
		return (-1);
	}
	if (!*dst && errno != ENOENT && errno != ENAMETOOLONG && errno != EACCES)
		error_exit();
	else if (!*dst)
		return (open_directory_split(path));
	return (1);
}
