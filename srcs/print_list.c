/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/29 22:17:52 by toliver           #+#    #+#             */
/*   Updated: 2018/08/29 22:19:25 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int					print_firstdirlist(t_file **list, int flags, int width)
{
	t_file			*ptr;

	listorder(list, flags);
	ptr = *list;
	while (ptr)
	{
		if (flags & MULTIFILE)
			ft_printf("%s:\n", ptr->name);
		if (!(fill_dir(ptr, flags)))
			print_permissiondenied(ptr);
		print_filelist(&ptr->list, flags, width);
		if (flags & BIGR_FLAG)
		{
			clearlist(&ptr->list);
			if (containadir(ptr->list))
			{
				ft_putchar('\n');
				recursive(&ptr->list, flags, width);
			}
			freelist(&ptr->list);
		}
		ptr = ptr->next;
	}
	freelist(list);
	return (1);
}

int					print_list_column(t_file *list, int width)
{
	int				fileperline;
	int				lines;
	int				colcounter;
	t_file			*tmp;
	t_file			*tmp2;

	column_varinit(width, &lines, &fileperline, list);
	if (fileperline == 0)
		return (print_list_onepercolumn(list));
	tmp = list;
	while (tmp != get_nnode(list, lines))
	{
		colcounter = 0;
		tmp2 = tmp;
		while (tmp2)
		{
			ft_printf("%-*s", get_biggestnamelen(list) + 1, tmp2->name);
			tmp2 = get_nnode(tmp2, lines);
			colcounter =
					((colcounter + 1) >= fileperline) ? 0 : (colcounter + 1);
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
		print_list_long(*filelist, width, flags);
	else
		print_list_column(*filelist, width);
	return (1);
}

int					print_errorlist(t_file **errorlist)
{
	t_file			*ptr;
	t_file			*ptr2;

	errorlistorder(errorlist);
	ptr = *errorlist;
	while (ptr)
	{
		ft_printf("ft_ls: %s: No such file or directory\n", ptr->name);
		ptr2 = ptr;
		ptr = ptr->next;
		delnode(errorlist, ptr2);
		freenode(ptr2);
	}
	return (1);
}
