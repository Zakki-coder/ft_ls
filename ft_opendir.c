#include "includes/ft_ls.h"

//     struct stat { /* when _DARWIN_FEATURE_64_BIT_INODE is NOT defined */
//         dev_t    st_dev;    /* device inode resides on */
//         ino_t    st_ino;    /* inode's number */
//         mode_t   st_mode;   /* inode protection mode */
//         nlink_t  st_nlink;  /* number of hard links to the file */
//         uid_t    st_uid;    /* user-id of owner */
//         gid_t    st_gid;    /* group-id of owner */
//         dev_t    st_rdev;   /* device type, for special file inode */
//         struct timespec st_atimespec;  /* time of last access */
//         struct timespec st_mtimespec;  /* time of last data modification */
//         struct timespec st_ctimespec;  /* time of last file status change */
//         off_t    st_size;   /* file size, in bytes */
//         quad_t   st_blocks; /* blocks allocated for file */
//         u_long   st_blksize;/* optimal file sys I/O ops blocksize */
//         u_long   st_flags;  /* user defined flags for file */
//         u_long   st_gen;    /* file generation number */
//     };

void print_permissions(unsigned int st_mode, struct dirent *dp)
{
	char permissions[11];

	ft_memset(permissions, '-', 10);
	permissions[10] = '\0';
	if (dp->d_type & DT_DIR)
		permissions[0] = 'd';
	else if (dp->d_type & DT_LNK)
		permissions[0] = 'l';
	if (st_mode & S_IRUSR)
		permissions[1] = 'r';
	if (st_mode & S_IWUSR)
		permissions[2] = 'w';
	if (st_mode & S_IXUSR)
		permissions[3] = 'x';
	if (st_mode & S_IRGRP)
		permissions[4] = 'r';
	if (st_mode & S_IWGRP)
		permissions[5] = 'w';
	if (st_mode & S_IXGRP)
		permissions[6] = 'x';
	if (st_mode & S_IROTH)
		permissions[7] = 'r';
	if (st_mode & S_IWOTH)
		permissions[8] = 'w';
	if (st_mode & S_IXOTH)
		permissions[9] = 'x';
	ft_printf("%-12s", permissions);
}

void print_time(t_stat *stat)
{
	char *time;
	char output[27];

	ft_bzero(output, 27);
	time = ctime(&stat->st_mtimespec.tv_sec);
	time += 8;
	ft_strncpy(output, time, 3);
	time -= 4;
	ft_strncat(output, time, 4);
	time += 7;
	ft_strncat(output, time, 5);
	ft_strncat(output, " ", 1);
	ft_printf("%*s", ft_strlen(output) + 1, output);
}

unsigned int nb_len(long long nb)
{
	int len;

	len = 1;
	while (nb >= 10)
	{
		++len;
		nb /= 10;
	}
	return (len);
}
/* TODO: We need to know the longest number of links and longest size beforehand to align correctly. Also the path/filename column should show links.
link is also shown in permissions section as l. All st_blocks must be calculated together*/

//We need the linked list in here.
/*
void width_and_total(t_stat *stat, t_width *widths)
{

}
*/

void print_stat(t_stat *stat, struct dirent *dp)
{
	printf("total %llu\n", stat->st_blocks);
//	printf("%d\n", stat->st_dev);
//	printf("%llu\n", stat->st_ino);
	print_permissions(stat->st_mode, dp);
	ft_printf("%-*u", ft_strlen(ft_itoa(stat->st_nlink)) + 1, stat->st_nlink);
//	ft_printf("%u\n", stat->st_uid);
	ft_printf("%-*s", ft_strlen(getpwuid(stat->st_uid)->pw_name) + 2, getpwuid(stat->st_uid)->pw_name);
//	ft_printf("%u\n", stat->st_gid);
	ft_printf("Fu: %d\n", stat->st_gid);
	ft_printf("Fu: %s\n", getgrgid(stat->st_gid));
//	TODO: getgrgid returns 0, maybe for . and ..?
	ft_printf("%s", getgrgid(stat->st_gid)->gr_name);
	//        struct timespec st_ctimespec;  /* time of last file status change */
	print_time(stat);
	ft_printf("%s\n", dp->d_name);
//	printf("%ld\n", stat->st_mtimespec.tv_nsec);
//	printf("%ld\n", stat->st_mtimespec.tv_sec);
//	printf("%d\n", stat->st_blksize);
//	printf("%u\n", stat->st_flags);
//	printf("%u\n", stat->st_gen);
}
//int stat(const char *restrict path, struct stat *restrict buf)
/*
void read_stat(char *restrict path)
{}
*/

//             ino_t      d_fileno;     /* file number of entry */
//             __uint64_t d_seekoff;    /* seek offset (optional, used by servers) */
//             __uint16_t d_reclen;     /* length of this record */
//             __uint16_t d_namlen;     /* length of string in d_name */
//             __uint8_t  d_type;       /* file type, see below */
//             char    d_name[1024];    /* name must be no longer than this */
//     };

//     typedef struct _dirdesc {
//             int     __dd_fd;      /* file descriptor associated with directory */
//             long    __dd_loc;     /* offset in current buffer */
//             long    __dd_size;    /* amount of data returned by getdirentries */
//             char    *__dd_buf;    /* data buffer */
//             int     __dd_len;     /* size of data buffer */
//             long    __dd_seek;    /* magic cookie returned by getdirentries */
//             long    __dd_rewind;  /* magic cookie for rewinding */
//             int     __dd_flags;   /* flags for readdir */
//             pthread_mutex_t __dd_lock; /* for thread locking */
//             struct _telldir *__dd_td; /* telldir position recording */
//     } DIR;

//int stat(const char *restrict path, struct stat *restrict buf)
/*
int main(void)
{
	DIR *dirp;
	t_file_node *head;
	struct dirent *dp;
	struct dirent *dp2;
	t_stat dir_stat;
	char *fd;
	char path[1024] = "./";
	int len;
	int ret = 5;

	dirp = opendir(path);
	dp = readdir(dirp);
	len = ft_strlen(path) + ft_strlen(dp->d_name);
	head = (t_file_node *)malloc(sizeof(t_file_node));
	head->path = (char *)ft_memalloc(len + 2);
		if (!head)
			;//bla bla
	ft_strcat(head->path, path);
//	ret = stat("../ft_ls", &dir_stat);
	ft_strcat(head->path, dp->d_name);
//	ft_strcat(head->path, "/");
	ret = stat(head->path, &head->stat);
	lstat(head->path, &head->lstat);
	print_stat(&head->stat, dp);
//	print_stat(&head->lstat, dp);
	while (dp)
	{
		dp = readdir(dirp);
		if (!dp)
			break;
		len = ft_strlen(path) + ft_strlen(dp->d_name);
		head->next = (t_file_node *)malloc(sizeof(t_file_node));
		head = head->next;
		head->path = (char *)ft_memalloc(len + 2);
		ft_strcat(head->path, path);
		ft_strcat(head->path, dp->d_name);
		ret = stat(head->path, &head->stat);
		lstat(head->path, &head->lstat);
		print_stat(&head->stat, dp);
	}
	return (0);
}
	*/

int main(void)
{
	t_file_node *head;
	char path[1024] = ".";

	head = create_list(opendir(path), path); 
	while (head)	
	{
		print_stat(&head->stat, &head->dp);
		head = head->next;
	}
	return (0);
}