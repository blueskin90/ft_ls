/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/29 22:17:52 by toliver           #+#    #+#             */
/*   Updated: 2018/08/31 23:56:58 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int					print_fdirlistloop(t_file **listptr, t_file *ptr,
					int flags, int width)
{
	clearlist(listptr);
	if (containadir(ptr->list))
	{
		ft_putchar('\n');
		recursive(listptr, flags, width);
	}
	freelist(listptr);
	return (1);
}

int					print_firstdirlist(t_file **list, int flags, int width)
{
	t_file			*ptr;
	int				isfirst;

	isfirst = 0;
	listorder(list, flags);
	ptr = *list;
	while (ptr)
	{
		if (isfirst == 1)
			ft_printf("\n");
		isfirst = ((isfirst == 1) ? 1 : 1);
		if (flags & MULTIFILE)
			ft_printf("%s:\n", ptr->name);
		if (!(fill_dir(ptr, flags)))
			print_permissiondenied(ptr);
		print_filelist(&ptr->list, flags, width);
		if (flags & BIGR_FLAG)
			print_fdirlistloop(&ptr->list, ptr, flags, width);
		ptr = ptr->next;
	}
	freelist(list);
	return (1);
}

int					print_list_column(t_file *list, int width)
{
	int				fileperline;
	int				lines;
	int				colcnt;
	t_file			*tmp;
	t_file			*tmp2;

	column_varinit(width, &lines, &fileperline, list);
	if (fileperline == 0)
		return (print_list_onepercolumn(list));
	if ((tmp = list) == NULL)
		return (0);
	while (tmp != get_nnode(list, lines))
	{
		colcnt = 0;
		tmp2 = tmp;
		while (tmp2)
		{
			ft_printf("%-*s", get_biggestnamelen(list) + 1, tmp2->name);
			tmp2 = get_nnode(tmp2, lines);
			colcnt = ((colcnt + 1) >= fileperline) ? 0 : (colcnt + 1);
		}
		ft_printf("\n");
		tmp = tmp->next;
	}
	return (1);
}

int					print_list_onepercolumn(t_file *list)
{
	t_file			*ptr;

	ptr = list;
	if (!ptr)
		return (0);
	while (ptr)
	{
		ft_printf("%s\n", ptr->name);
		ptr = ptr->next;
	}
	return (1);
}

int					print_filelist(t_file **filelist, int flags, int width)
{
	listorder(filelist, flags);
	if (flags & LONG_FLAGS)
		return (print_list_long(*filelist, width, flags));
	else
		return (print_list_column(*filelist, width));
	return (1);
}
