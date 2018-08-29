/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/22 16:48:21 by toliver           #+#    #+#             */
/*   Updated: 2018/08/29 22:20:27 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int					nbrlen(long long int nbr)
{
	int				i;

	i = 0;
	if (nbr == 0)
		return (1);
	while (nbr / 10 || nbr % 10)
	{
		i++;
		nbr = nbr / 10;
	}
	return (i);
}

int					column_varinit(int width, int *lines, int *fileperline,
					t_file *list)
{
	int				listlen;

	listlen = get_listlen(list);
	*fileperline = width / (get_biggestnamelen(list) + 1);
	if (fileperline == 0)
		return (0);
	*lines = (listlen / *fileperline) + ((listlen % *fileperline == 0) ? 0 : 1);
	*fileperline = (*lines != 0) ? (listlen / *lines) : listlen;
	return (1);
}

int					print_permissiondenied(t_file *file)
{
	ft_printf("ft_ls: %s: %s\n", file->name, strerror(errno));
	return (1);
}

int					containadir(t_file *list)
{
	t_file			*ptr;

	ptr = list;
	while (ptr)
	{
		if (S_ISDIR(ptr->stat.st_mode))
			break ;
		ptr = ptr->next;
	}
	if (ptr)
		return (1);
	return (0);
}
