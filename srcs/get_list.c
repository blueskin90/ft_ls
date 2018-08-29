/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/29 21:56:39 by toliver           #+#    #+#             */
/*   Updated: 2018/08/29 21:57:36 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

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
