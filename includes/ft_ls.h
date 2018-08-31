/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/19 23:27:21 by toliver           #+#    #+#             */
/*   Updated: 2018/08/30 19:28:35 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "libft.h"
# include "libftprintf.h"
# include <dirent.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/ioctl.h>
# include <sys/xattr.h>
# include <sys/errno.h>
# include <grp.h>
# include <time.h>
# include <pwd.h>
# include <uuid/uuid.h>
# include <limits.h>

# define MULTIFILE 0x80000000
# define BIGR_FLAG 64
# define A_FLAG 32
# define G_FLAG 16
# define L_FLAG 8
# define R_FLAG 4
# define T_FLAG 2
# define F_FLAG 1
# define LONG_FLAGS 24
# define INFO_FLAGS 26
# define SORT_FLAGS 6

typedef struct	s_infos
{
	char			permissions[12];
	int				linknumber;
	char			*usrname;
	int				usrnum;
	char			*grpname;
	int				grpnum;
	long long int	size;
	int				blocksize;
	char			*month;
	int				day;
	int				hour;
	int				min;
	char			*linkname;
}				t_infos;

typedef struct	s_file
{
	char			*name;
	char			*path;
	char			iserror;
	t_infos			infos;
	DIR				*dirp;
	struct stat		stat;
	struct s_file	*next;
	struct s_file	*list;
	struct s_file	*errorlist;
}				t_file;

typedef struct	s_param
{
	int			width;
	int			flags;
	t_file		*list;
	t_file		*filelist;
	t_file		*cantopenlist;
	t_file		*errorlist;
}				t_param;

/*
**	Recursive functions
*/

int				recursive(t_file **list, int flags, int width);
int				recursiveelse(t_file **list, t_file *file, int flags,
								int width);
int				newline(int *isfirst);

/*
** Utility functions
*/

int				iscorrectflag(char c);
int				nbrlen(long long int nbr);
int				get_linkslen(t_file *list);
int				get_uidlen(t_file *list);
int				get_grgidlen(t_file *list);
int				get_biggestsize(t_file *list);
int				get_biggestday(t_file *list);
int				containadir(t_file *list);

/*
** Printing functions
*/

int				print_list_onepercolumn(t_file *list);
int				print_errorlist(t_file **errorlist);
int				print_filelist(t_file **filelist, int flags, int width);
int				print_list_long(t_file *list, int width, int flags);
int				print_list_column(t_file *list, int width);
int				print_firstdirlist(t_file **list, int flags, int width);
int				print_fdirlistloop(t_file **list, t_file *ptr, int flags,
				int width);
int				print_permissiondenied(t_file *file);
int				print_link(t_file *file);
int				print_size(int biggest, t_file *file);
int				print_time(t_file *list, t_file *ptr);
int				print_users(t_file *list, t_file *ptr, int flags);
int				print_blksize(t_file *list);

/*
** Initialization functions
*/

int				column_varinit(int width, int *lines, int *fileperline,
								t_file *list);
int				envinit(t_param *env);

/*
** Parsing functions
*/

int				clearlist(t_file **file);
int				fill_dir(t_file *file, int flags);
int				addfile(struct dirent *filetoadd, t_file *dir, int flags);
int				parsing(int argc, char **argv, t_param *env);
int				flagset(t_param *env, char *str);
int				illegal_option(char c);
int				fileadd(t_file **list, char *name, char *path, int flags);
int				first_check(t_param *env);
int				get_info(t_file *file, int flags);
int				fill_dir(t_file *file, int flags);

/*
**	List manipulation functions
*/

t_file			*nodealloc(char *name, char *path, int flags);
int				addnode(t_file **list, t_file *nodetoadd);
int				addfirstnode(t_file **list, t_file *nodetoadd);
int				delnode(t_file **list, t_file *nodetodel);
int				movenode(t_file **listfrom, t_file *filetomove,
					t_file **listto);
int				movenodefirst(t_file **listfrom, t_file *filetomove,
					t_file **listto);
int				freenode(t_file *node);
int				freelist(t_file **list);
int				errorlistorder(t_file **list);
t_file			*get_first_time(t_file **list);
t_file			*get_first_alpha(t_file **list);
int				listorder(t_file **list, int flags);
t_file			*get_nnode(t_file *list, int number);
int				get_listlen(t_file *list);
int				get_biggestnamelen(t_file *list);

#endif
