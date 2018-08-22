/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_handling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/21 23:00:55 by toliver           #+#    #+#             */
/*   Updated: 2018/08/22 22:56:30 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int					addfile(struct dirent *filetoadd, t_file *file, int flags)
{
	char			*nodepath;
	char			*tmp;
	
	nodepath = ft_strjoin(file->path, "/");
	tmp = nodepath;
	nodepath = ft_strjoin(tmp, filetoadd->d_name);
	free(tmp);
	addnode(&file->list, nodealloc(ft_strdup(filetoadd->d_name), nodepath, flags));
	return (1);
}

t_file				*nodealloc(char *name, char *path, int flags)
{
	t_file			*file;

	if (!(file = (t_file*)malloc(sizeof(t_file))))
		return (NULL);  // quoi faire si ca foire
	file->name = name;
	file->path = (path == NULL) ? ft_strdup(name) : path;
	file->iserror = 0;
	file->dirp = NULL;
	file->next = NULL;
	file->list = NULL;
	file->errorlist = NULL;
	get_info(file, flags);
	return (file);
}

int			addfirstnode(t_file **list, t_file *nodetoadd)
{
	if (*list == NULL)
		*list = nodetoadd;
	else
	{
		nodetoadd->next = *list;
		*list = nodetoadd;
	}
	return (1);

}

int			addnode(t_file **list, t_file *nodetoadd)
{
	t_file	*ptr;
	if (*list == NULL)
		*list = nodetoadd;
	else
	{
		ptr = *list;
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = nodetoadd;
	}
	return (1);
}

int			delnode(t_file **list, t_file *nodetodel)
{
	t_file	*ptr;

	if (*list == nodetodel)
		*list = nodetodel->next;
	else
	{
		ptr = *list;
		while (ptr->next != nodetodel)
			ptr = ptr->next;
		ptr->next = ptr->next->next;
	}
	nodetodel->next = NULL;
	return (1);
}

int			movenode(t_file **listfrom, t_file *filetomove, t_file **listto)
{
	delnode(listfrom, filetomove);
	addnode(listto, filetomove);
	return (1);
}

int			movenodefirst(t_file **listfrom, t_file *filetomove, t_file **listto)
{
	delnode(listfrom, filetomove);
	addfirstnode(listto, filetomove);
	return (1);
}

int			freenode(t_file *node)
{
	free(node->name);
	free(node->path);
	freelist(&node->list);
	freelist(&node->errorlist);
	free(node);
	return (1);	
}

int			freelist(t_file **list)
{
	t_file	*ptr;
	t_file	*ptr2;

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

t_file		*get_first_time(t_file **list)
{
	t_file	*file;
	t_file	*tmp;

	file = *list;
	tmp = *list;
	while (tmp)
	{
		if (tmp == file)
			tmp = tmp->next;
		else
		{
			if (tmp->stat.st_mtime > file->stat.st_mtime || 
					(tmp->stat.st_mtime == file->stat.st_mtime &&
					ft_strcmp(file->name, tmp->name) > 0))
				file = tmp;
			tmp = tmp->next;
		}
	}
	return (file);
}

t_file		*get_first_alpha(t_file **list)
{
	t_file	*file;
	t_file	*tmp;

	file = *list;
	tmp = *list;
	if (tmp && !(tmp->next))
		return (*list);
	while (tmp)
	{
		if (tmp == file)
			tmp = tmp->next;
		else
		{
			if (ft_strcmp(file->name, tmp->name) > 0)
				file = tmp;
			tmp = tmp->next;
		}
	}
	return (file);
}

int			listorder(t_file **list, int flags)
{
	t_file	*ptr;
	t_file	*newlist;

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

int			errorlistorder(t_file **list)
{
	t_file	*ptr;
	t_file	*newlist;

	newlist = NULL;
	while ((ptr = get_first_alpha(list)))
		movenode(list, ptr, &newlist);
	*list = newlist;
	return (1);
}

t_file		*get_nnode(t_file *list, int number)
{
	t_file	*tmp;

	tmp = list;
	while (tmp && number)
	{
		tmp = tmp->next;
		number--;
	}
	return (tmp);
}

int			get_listlen(t_file *list)
{
	int		i;
	t_file	*tmp;

	tmp = list;
	i = 0;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

int			get_biggestnamelen(t_file *list)
{
	t_file	*tmp;
	int		biggest;
	int		strlen;

	biggest = 0;
	tmp = list;
	while (tmp)
	{
		if ((strlen = (int)ft_strlen(tmp->name)) > biggest)
			biggest = strlen;
		tmp = tmp->next;
	}
	return (biggest);
}
