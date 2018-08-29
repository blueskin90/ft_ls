/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recursive.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/29 22:11:01 by toliver           #+#    #+#             */
/*   Updated: 2018/08/29 22:11:42 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int				recursiveelse(t_file **list, t_file *file, int flags, int width)
{
	ft_printf("%s:\n", file->path);
	print_filelist(list, flags, width);
	clearlist(list);
	if (containadir(file->list))
	{
		ft_putchar('\n');
		recursive(list, flags, width);
	}
	freelist(list);
	return (1);
}

int				newline(int *isfirst)
{
	if (*isfirst == 0)
		*isfirst = 1;
	else
		ft_putchar('\n');
	return (1);
}

int				recursive(t_file **list, int flags, int width)
{
	t_file		*file;
	int			isfirst;

	isfirst = 0;
	file = *list;
	if (!list)
		return (0);
	while (file)
	{
		if (S_ISDIR(file->stat.st_mode))
		{
			newline(&isfirst);
			if (!(fill_dir(file, flags)))
			{
				ft_printf("%s:\n", file->path);
				print_permissiondenied(file);
				if (file->next)
					ft_putchar('\n');
			}
			else
				recursiveelse(&file->list, file, flags, width);
		}
		file = file->next;
	}
	return (1);
}
