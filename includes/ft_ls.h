/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 22:21:26 by jniemine          #+#    #+#             */
/*   Updated: 2022/09/24 18:22:53 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <dirent.h>
# include <time.h>
# include <errno.h>
# include <sys/stat.h>
# include <pwd.h>
# include <grp.h>
# include <sys/ioctl.h>
# include <sys/xattr.h>
# include <sys/acl.h>
# include "../libft/ft_printf/includes/ft_printf.h"

# define EXT_ATTR		1
# define LONG_LST		2
# define RECURSIVE		4
# define REVERSE_ORDER	8 
# define ALL			16
# define TIME_ORDER		32
# define PRINT_DIR_NAME	64
# define ONE_COLUMN		128
# define ACL			256
# define PRINT_NL		512

typedef struct stat			t_stat;
typedef struct dirent		t_dir;
typedef struct s_file_node	t_file_node;

typedef struct s_dir_and_paths
{
	DIR		**open_dir;
	char	**dir_paths;
	char	**arg_paths;
	int		i;
	int		j;
}	t_paths;

typedef struct s_width
{
	unsigned int	is_file;
	unsigned int	link_col;
	unsigned int	size_col;
	unsigned int	max_usr_col;
	unsigned int	max_grp_col;
	unsigned int	total_size;
	unsigned int	flags;
	unsigned int	dir_amount;
	unsigned int	file_amount;
	unsigned int	longest_filename;
	char			*dir_path;
	struct winsize	window_size;
}	t_width;

struct s_file_node
{
	int				is_hidden;
	int				is_head;
	unsigned int	total_blocks;
	char			*file_name;
	t_stat			stat;
	t_stat			lstat;
	unsigned int	d_minor;
	unsigned int	d_major;
	char			*usr;
	char			*grp;
	int				namelen;
	unsigned int	type;
	unsigned int	flags;
	acl_t			acl;
	ssize_t			ext_attr_len;
	ssize_t			ext_attr_p_len;
	char			*ext_attr;
	char			*dir_path;
	char			*path;
	t_file_node		*next;
};

void			reverse_lst(t_file_node **head);
int				reverse_time_compare(struct stat t1, struct stat t2);
void			hex_print(t_file_node *h);
void			free_node(t_file_node **head);
void			create_filepointer(char **file_names, int k, t_width *widths);
void			create_file_list(t_dir **fileps, t_width *w, char **root_paths);
void			make_columns(t_file_node *h, int rws, int w_width, char **dirs);
void			print_extended_attributes(t_file_node *head, int flags);
void			print_permissions(unsigned int st_mode, t_file_node *node);
void			handle_path(char *r_path, t_file_node *h, t_dir *dp, int flags);
void			get_t_dir_info(t_dir *filep, t_file_node *node);
int				get_stat_info(t_file_node *node);
void			update_widths(t_file_node *head, t_width *widths);
t_file_node		*create_node(void);
int				read_stream(DIR *dirp, t_dir **filep);
void			sort_arguments(int argc, char **argv, t_width *w, t_paths path);
int				open_directory(char *path, DIR **dst, t_width *w);
void			choose_output_format(t_file_node *h, t_width *w, char **dpaths);
int				time_compare(struct stat t1, struct stat t2);
int				reverse_strcmp(const char *s1, const char *s2);
t_file_node		*sort(t_file_node **head, int flags, t_width *widths);
t_file_node		*create_list(DIR *dirp, char *dir_paths, t_width *widths);
unsigned int	nb_len(long long nb);
void			error_exit(void);
int				ls_get_flags(int argc, char **argv, unsigned int *flags);
void			recursive_traverse(char **paths, int i, t_width *widths_flags);
void			print_long_format(t_file_node *h, t_width w, char **dir_paths);
void			free_lst(t_file_node *head);
void			print_columns(t_file_node *head, t_width *w, char **dir_paths);
#endif