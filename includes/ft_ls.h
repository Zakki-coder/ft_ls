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

#include "../libft/libft.h"
#include "../libft/ft_printf/includes/ft_printf.h"

typedef struct stat		t_stat;
typedef struct dirent		t_dir; 
typedef struct s_file_node	t_file_node;


typedef struct s_width
{
	unsigned int	link_col;
	unsigned int	size_col;
	unsigned int	total_size;
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

t_file_node *create_list(DIR *dirp, char *dir_paths, t_width *widths);
void print_stat(t_file_node *node, t_width *widths);
unsigned int nb_len(long long nb);
void error_exit(void);
#endif