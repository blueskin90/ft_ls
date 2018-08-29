/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/20 17:41:39 by toliver           #+#    #+#             */
/*   Updated: 2018/08/29 19:29:36 by toliver          ###   ########.fr       */
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

int					get_info(t_file *file, int flags)
{
	lstat(file->path, &file->stat);
	get_file_type(file);
	if (flags & INFO_FLAGS)
		get_more_info(file, flags);
	return (1);
}

int					fileadd(t_file **list, char *name, char *path, int flags)
{
	t_file			*tmp;

	if (*list == NULL)
		*list = nodealloc(name, path, flags);
	else
	{
		tmp = *list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = nodealloc(name, path, flags);
	}
	(void)path;
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

int					iscorrect(char c)
{
	if (c == 'R' || c == 'a' || c == 'g' || c == 'l' || c == 'r' || c == 't')
		return (1);
	return (0);
}

int					parsing(int argc, char **argv, t_param *env)
{
	int				i;

	i = 1;
	while (i < argc)
	{
		if (argv[i][0] != '-'
				|| (argv[i][0] == '-' && !(iscorrect(argv[i][1]))))
			break ;
		else
			flagset(env, argv[i]);
		i++;
	}
	if (i >= argc)
		fileadd(&env->list, ft_strdup("."), NULL, env->flags);
	else
	{
		if (i < argc - 1)
			env->flags |= MULTIFILE;
		while (i < argc)
		{
			fileadd(&env->list, ft_strdup(argv[i]), NULL, env->flags);
			i++;
		}
	}
	return (1);
}

int					first_check(t_param *env)
{
	t_file			*listptr;

	listptr = env->list;
	while (listptr)
	{
		if (listptr->infos.permissions[0] != 'd')
		{
			movenode(&env->list, listptr, (listptr->infos.permissions[0] == '!')
					? &env->errorlist : &env->filelist);
			listptr = env->list;
		}
		else
			listptr = listptr->next;
	}
	print_errorlist(&env->errorlist);
	print_filelist(&env->filelist, env->flags, env->width);
	if ((env->errorlist || env->filelist) && env->list)
		ft_printf("\n");
	print_firstdirlist(&env->list, env->flags, env->width);
	return (1);
}

int			fill_dir(t_file *dir, int flags)
{
	struct dirent	*currentdir;

	if (!(dir->dirp = opendir(dir->path)))
		return (0);
	while ((currentdir = readdir(dir->dirp)))
	{
		if ((flags & A_FLAG) || (!(flags & A_FLAG)
					&& currentdir->d_name[0] != '.'))
		{
			addfile(currentdir, dir, flags);
		}
	}
	closedir(dir->dirp);
	listorder(&dir->list, flags);
	return (1);
}
