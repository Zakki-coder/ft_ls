/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 20:13:05 by jniemine          #+#    #+#             */
/*   Updated: 2022/09/14 21:13:47 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

/* It has already been confirmed that filename exist at path */
static t_dir	*search_file_pointer(char *path, char *filename)
{
	DIR		*dirp;
	t_dir	*filep;

	filep = NULL;
	dirp = NULL;
	if (open_directory(path, &dirp, NULL) == 1)
		filep = read_stream(dirp);
	while (filep)
	{
		if (ft_strcmp(filep->d_name, filename) == 0)
			return (filep);
		filep = read_stream(dirp);
	}
	return (filep);
}

static void	get_name_and_path(char *arg_names, char *filename, char *root_path)
{
	char	*slash;
	int		n;
	int		len;

	n = 1;
	len = 0;
	slash = ft_strrchr(arg_names, '/');
	if (!slash)
	{
		ft_strcpy(filename, arg_names);
		ft_strcpy(root_path, ".");
	}
	else
	{
		len = ft_strlen(arg_names) - ft_strlen(slash + n);
		ft_strcat(filename, slash + n);
		ft_strncat(root_path, arg_names, len);
	}
}

/* file_names are pointers to program arguments so they dont need freeing */
void	create_filepointer(char **file_names, int k, t_width *widths)
{
	char	filename[1024];
	char	path[1024];
	char	**root_paths;
	t_dir	**filepointers;
	int		i;

	filepointers = (t_dir **)ft_memalloc(sizeof(*filepointers) * k + 1);
	root_paths = (char **)ft_memalloc(sizeof(*root_paths) * k + 1);
	filepointers[k] = NULL;
	root_paths[k] = NULL;
	i = 0;
	while (file_names[i] && i < k)
	{
		ft_bzero(path, 1024);
		ft_bzero(filename, 1024);
		get_name_and_path(file_names[i], filename, path);
		root_paths[i] = (char *)ft_memalloc(ft_strlen(path) + 1);
		ft_strcpy(root_paths[i], path);
		filepointers[i++] = search_file_pointer(path, filename);
		filepointers[i] = NULL;
	}
	free(file_names);
	create_file_list(filepointers, widths, root_paths);
	widths->flags |= PRINT_DIR_NAME;
}
