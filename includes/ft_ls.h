#ifndef FT_LS
# define FT_LS

#include <stdio.h> //DEEELT

#include <dirent.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <pwd.h>
#include <grp.h>
#include <uuid/uuid.h>
#include <time.h>
#include <sys/ioctl.h>

#include "../libft/libft.h"
#include "../libft/ft_printf/includes/ft_printf.h"

#define LONG_LST		2
#define RECURSIVE		4
#define REVERSE_ORDER	8 
#define ALL				16
#define TIME_ORDER		32

#define ALLOWED_OPTIONS "-lRrat"
typedef struct stat		t_stat;
typedef struct dirent		t_dir; 
typedef struct s_file_node	t_file_node;

typedef struct s_width
{
	unsigned int	link_col;
	unsigned int	size_col;
	unsigned int	total_size;
	unsigned int	flags;
	unsigned int	dir_amount;
	unsigned int	file_amount;
	unsigned int	longest_filename;
	struct winsize	window_size;
}	t_width;

struct s_file_node
{
	int				is_head;
	t_dir 			dp;
	unsigned int	total_blocks;
	char			*file_name;
	t_stat			stat;
	t_stat			lstat;
	int				namelen;
	int				type;
	char			*path;
	t_file_node 	*next;
};

void print_lst(t_file_node *head); //DEL SO MUCHO
void lst_iter_loop(t_file_node **head, int (*f)(const char *, const char *));
int lst_iter(t_file_node **head, int (*f)(const char *s1, const char *s2));
t_file_node *create_list(DIR *dirp, char *dir_paths, t_width *widths);
void print_stat(t_file_node *node, t_width *widths, char **dir_paths, int *i);
unsigned int nb_len(long long nb);
void error_exit(void);
int ls_get_flags(int argc, char **argv, unsigned int *flags);
DIR *open_directory(char *path);
void recursive_traverse(char **paths, int i, t_width *widths_flags);
void print_loop(t_file_node *head, t_width widths, char **dir_paths);
void debugger(char **paths);
void free_lst(t_file_node *head);
void print_columns(t_file_node *head, t_width *widths);

#endif