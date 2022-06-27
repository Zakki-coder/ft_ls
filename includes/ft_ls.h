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
#include <time.h>

#include "../libft/libft.h"
#include "../libft/ft_printf/includes/ft_printf.h"

typedef struct stat		t_stat;
typedef struct dirent		t_dir; 
typedef struct s_file_node	t_file_node;

t_file_node *create_list(DIR *dirp, char *dir_paths);

struct s_file_node
{
	t_dir 			dp;
	t_stat			stat;
	t_stat			lstat;
	unsigned int	total_blocks;
//	char			*file_name;
	char			*path;
	t_file_node 	*next;
};

typedef struct s_width
{
	unsigned int	link_col;
	unsigned int	size_col;
}	t_width;

#endif