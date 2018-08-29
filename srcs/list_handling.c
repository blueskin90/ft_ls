/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_handling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/21 23:00:55 by toliver           #+#    #+#             */
/*   Updated: 2018/08/29 22:16:57 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int					addfile(struct dirent *filetoadd, t_file *file, int flags)
{
	char			*nodepath;
	char			*tmp;

	if (file->path[0] != '/' || (file->path[0] == '/' && file->path[1] != 0))
	{
		if (!(nodepath = ft_strjoin(file->path, "/")))
			exit(1);
		tmp = nodepath;
		if (!(nodepath = ft_strjoin(tmp, filetoadd->d_name)))
			exit(1);
		free(tmp);
	}
	else
	{
		tmp = file->path;
		if (!(nodepath = ft_strjoin(tmp, filetoadd->d_name)))
			exit(1);
	}
	addnode(&file->list, nodealloc(ft_strdup(filetoadd->d_name), nodepath,
				flags));
	return (1);
}

int					freelist(t_file **list)
{
	t_file			*ptr;
	t_file			*ptr2;

	ptr = *list;
	while (ptr)
	{
		ptr2 = ptr;
		ptr = ptr->next;
		delnode(list, ptr2);
		freenode(ptr2);
	}
	*list = NULL;
	return (1);
}

int					listorder(t_file **list, int flags)
{
	t_file			*ptr;
	t_file			*newlist;

	newlist = NULL;
	if ((flags & T_FLAG) || !(flags & F_FLAG))
	{
		if (flags & T_FLAG)
			while ((ptr = get_first_time(list)))
			{
				if (flags & R_FLAG)
					movenodefirst(list, ptr, &newlist);
				else
					movenode(list, ptr, &newlist);
			}
		else
			while ((ptr = get_first_alpha(list)))
			{
				if (flags & R_FLAG)
					movenodefirst(list, ptr, &newlist);
				else
					movenode(list, ptr, &newlist);
			}
		*list = newlist;
	}
	return (1);
}

int					errorlistorder(t_file **list)
{
	t_file			*ptr;
	t_file			*newlist;

	newlist = NULL;
	while ((ptr = get_first_alpha(list)))
		movenode(list, ptr, &newlist);
	*list = newlist;
	return (1);
}

int					clearlist(t_file **list)
{
	t_file			*ptr;
	t_file			*tmp;

	ptr = *list;
	while (ptr)
	{
		if (!(S_ISDIR(ptr->stat.st_mode)) || (S_ISDIR(ptr->stat.st_mode)
			&& (ft_strcmp(ptr->name, ".") == 0
				|| ft_strcmp(ptr->name, "..") == 0)))
		{
			tmp = ptr->next;
			delnode(list, ptr);
			freenode(ptr);
			ptr = tmp;
		}
		else
			ptr = ptr->next;
	}
	return (1);
}
