/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/20 17:41:39 by toliver           #+#    #+#             */
/*   Updated: 2018/08/31 23:57:12 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int					iscorrect(char c)
{
	if (c == 'R' || c == 'a' || c == 'g' || c == 'l' || c == 'r' || c == 't')
		return (1);
	return (0);
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
	return (1);
}

int					parsing(int argc, char **argv, t_param *env)
{
	int				i;

	i = 0;
	while (++i < argc)
	{
		if (ft_strcmp(argv[i], "--") == 0)
		{
			i++;
			break ;
		}
		if (argv[i][0] != '-')
			break ;
		else
			flagset(env, argv[i]);
	}
	if (i >= argc)
		return (fileadd(&env->list, ft_strdup("."), NULL, env->flags));
	env->flags |= ((i < argc - 1) ? MULTIFILE : 0);
	while (i < argc)
	{
		fileadd(&env->list, ft_strdup(argv[i]), NULL, env->flags);
		i++;
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
	if (print_errorlist(&env->errorlist) && (env->filelist || env->list))
		ft_printf("\n");
	if (print_filelist(&env->filelist, env->flags, env->width) && env->list)
		ft_printf("\n");
	print_firstdirlist(&env->list, env->flags, env->width);
	return (1);
}

int					fill_dir(t_file *dir, int flags)
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
