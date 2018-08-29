/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_handling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/29 22:00:48 by toliver           #+#    #+#             */
/*   Updated: 2018/08/29 22:04:23 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_file				*nodealloc(char *name, char *path, int flags)
{
	t_file			*file;

	if (!(file = (t_file*)malloc(sizeof(t_file))))
		exit(1);
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

int					addfirstnode(t_file **list, t_file *nodetoadd)
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

int					addnode(t_file **list, t_file *nodetoadd)
{
	t_file			*ptr;

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

int					delnode(t_file **list, t_file *nodetodel)
{
	t_file			*ptr;

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

int					freenode(t_file *node)
{
	free(node->name);
	free(node->path);
	freelist(&node->list);
	freelist(&node->errorlist);
	free(node);
	return (1);
}
