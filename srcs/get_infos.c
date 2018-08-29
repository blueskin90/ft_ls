/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_infos.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/29 22:06:01 by toliver           #+#    #+#             */
/*   Updated: 2018/08/29 22:07:42 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int					get_file_type(t_file *file)
{
	ft_bzero(file->infos.permissions, 11);
	if (S_ISREG(file->stat.st_mode))
		file->infos.permissions[0] = '-';
	else if (S_ISDIR(file->stat.st_mode))
		file->infos.permissions[0] = 'd';
	else if (S_ISCHR(file->stat.st_mode))
		file->infos.permissions[0] = 'c';
	else if (S_ISBLK(file->stat.st_mode))
		file->infos.permissions[0] = 'b';
	else if (S_ISFIFO(file->stat.st_mode))
		file->infos.permissions[0] = 'f';
	else if (S_ISLNK(file->stat.st_mode))
		file->infos.permissions[0] = 'l';
	else if (S_ISSOCK(file->stat.st_mode))
		file->infos.permissions[0] = 's';
	else
		file->infos.permissions[0] = '!';
	return (1);
}

int					get_more_info(t_file *file, int flags)
{
	file->infos.permissions[1] = ((file->stat.st_mode & S_IRUSR) ? 'r' : '-');
	file->infos.permissions[2] = ((file->stat.st_mode & S_IWUSR) ? 'w' : '-');
	file->infos.permissions[3] = ((file->stat.st_mode & S_IXUSR) ? 'x' : '-');
	file->infos.permissions[4] = ((file->stat.st_mode & S_IRGRP) ? 'r' : '-');
	file->infos.permissions[5] = ((file->stat.st_mode & S_IWGRP) ? 'w' : '-');
	file->infos.permissions[6] = ((file->stat.st_mode & S_IXGRP) ? 'x' : '-');
	file->infos.permissions[7] = ((file->stat.st_mode & S_IROTH) ? 'r' : '-');
	file->infos.permissions[8] = ((file->stat.st_mode & S_IWOTH) ? 'w' : '-');
	file->infos.permissions[9] = ((file->stat.st_mode & S_IXOTH) ? 'x' : '-');
	file->infos.permissions[10] = ' ';
	(void)flags;
	return (1);
}

int					flagset(t_param *env, char *str)
{
	int				i;

	i = 0;
	while (str[++i])
	{
		if (str[i] == 'R')
			env->flags |= BIGR_FLAG;
		else if (str[i] == 'a')
			env->flags |= A_FLAG;
		else if (str[i] == 'l')
			env->flags |= L_FLAG;
		else if (str[i] == 'r')
			env->flags |= R_FLAG;
		else if (str[i] == 't')
			env->flags |= T_FLAG;
		else if (str[i] == 'f')
			env->flags |= (F_FLAG + A_FLAG);
		else if (str[i] == 'g')
			env->flags |= G_FLAG;
		else
			illegal_option(str[i]);
	}
	if (env->flags & T_FLAG && env->flags & F_FLAG)
		env->flags ^= T_FLAG;
	return (1);
}

int					get_info(t_file *file, int flags)
{
	lstat(file->path, &file->stat);
	get_file_type(file);
	if (flags & INFO_FLAGS)
		get_more_info(file, flags);
	return (1);
}
