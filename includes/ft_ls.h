/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/19 23:27:21 by toliver           #+#    #+#             */
/*   Updated: 2018/08/22 00:08:46 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "libft.h"
# include "libftprintf.h"

#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <sys/xattr.h>
#include <sys/errno.h>
#include <grp.h>
#include <time.h>
#include <pwd.h>
#include <uuid/uuid.h>

#define MULTIFILE 0x80000000 // multi output
#define BIGR_FLAG 64 // recursive
#define A_FLAG 32 // n'ignore pas les fichiers qui commencent par .
#define G_FLAG 16 // comme -l mais display le groupe au lieu de l'owner
#define L_FLAG 8 // long output
#define R_FLAG 4 // reverse sorting order
#define T_FLAG 2 // range par time modified (plus recent first) avant de les ranger par ordre lexical
#define F_FLAG 1 // output not sorted, active le a flag

#define LONG_FLAGS 24
#define INFO_FLAGS 26
#define SORT_FLAGS 6

typedef struct	s_infos
{
	char		permissions[10];
}				t_infos;

typedef struct	s_file
{
	// rajouter un parametre selon le type d'erreur
	char			*name;
	char			*path;
	char			iserror;
	t_infos			infos;
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
	t_file		*errorlist;
}				t_param;


/*
** Initialization functions
*/

int				envinit(t_param *env);

/*
** Parsing functions
*/

int				parsing(int argc, char **argv, t_param *env);
int				flagset(t_param *env, char *str);
int				illegal_option(char c);
int				fileadd(t_file **list, char *name, char *path, int flags);
int				first_check(t_param *env);
int				get_info(t_file *file, int flags);

/*
**	List manipulation functions
*/

t_file			*nodealloc(char *name, char *path, int flags);
int				addnode(t_file **list, t_file *nodetoadd);
int				addfirstnode(t_file **list, t_file *nodetoadd);
int				delnode(t_file **list, t_file *nodetodel);
int				movenode(t_file **listfrom, t_file *filetomove, t_file **listto);
int				movenodefirst(t_file **listfrom, t_file *filetomove, t_file **listto);
int				freenode(t_file *node);
int				freelist(t_file **list);
int				errorlistorder(t_file **list);
t_file			*get_first_time(t_file **list);
t_file			*get_first_alpha(t_file **list);
int				listorder(t_file **list, int flags);

#endif
