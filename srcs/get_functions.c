/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/29 22:09:51 by toliver           #+#    #+#             */
/*   Updated: 2018/08/29 22:10:32 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int					get_linkslen(t_file *list)
{
	t_file			*ptr;
	long long int	biggest;
	long long int	size;

	biggest = 0;
	ptr = list;
	while (ptr)
	{
		if ((size = nbrlen(ptr->stat.st_nlink)) > biggest)
			biggest = size;
		ptr = ptr->next;
	}
	return (biggest);
}

int					get_uidlen(t_file *list)
{
	t_file			*ptr;
	long long int	biggest;
	long long int	size;

	biggest = 0;
	ptr = list;
	while (ptr)
	{
		if (getpwuid(ptr->stat.st_uid) == NULL)
		{
			if ((size = nbrlen(ptr->stat.st_uid)) > biggest)
				biggest = size;
		}
		else if ((size = ft_strlen(getpwuid(ptr->stat.st_uid)->pw_name))
				> biggest)
			biggest = size;
		ptr = ptr->next;
	}
	return (biggest);
}

int					get_grgidlen(t_file *list)
{
	t_file			*ptr;
	long long int	biggest;
	long long int	size;

	biggest = 0;
	ptr = list;
	while (ptr)
	{
		if ((getgrgid(ptr->stat.st_gid)) == NULL)
		{
			if ((size = nbrlen(ptr->stat.st_gid)) > biggest)
				biggest = size;
		}
		else if ((size = ft_strlen(getgrgid(ptr->stat.st_gid)->gr_name))
				> biggest)
			biggest = size;
		ptr = ptr->next;
	}
	return (biggest);
}

int					get_biggestsize(t_file *list)
{
	t_file			*ptr;
	long long int	biggest;
	long long int	size;

	biggest = 0;
	ptr = list;
	while (ptr)
	{
		if ((size = nbrlen(ptr->stat.st_size)) > biggest)
			biggest = size;
		ptr = ptr->next;
	}
	return (biggest);
}

int					get_biggestday(t_file *list)
{
	t_file			*ptr;
	long long int	biggest;
	long long int	size;

	biggest = 0;
	ptr = list;
	while (ptr)
	{
		if ((size = nbrlen(ft_atoi(ctime(&ptr->stat.st_ctimespec.tv_sec) + 7)))
				> biggest)
			biggest = size;
		ptr = ptr->next;
	}
	return (biggest);
}
