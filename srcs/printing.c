/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/22 16:48:21 by toliver           #+#    #+#             */
/*   Updated: 2018/08/23 16:56:12 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int					print_filelist(t_file **filelist, int flags, int width)
{
	listorder(filelist, flags);
	if (flags & L_FLAG)
		print_list_long(*filelist, width);
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

int					nbrlen(long long int nbr)
{
	int				i;

	i = 0;
	while (nbr / 10)
	{
		i++;
		nbr = nbr/10;
	}
	i++;
	return (i);
}

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
		if ((size = ft_strlen(getpwuid(ptr->stat.st_uid)->pw_name)) > biggest)
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
		if ((size = ft_strlen(getgrgid(ptr->stat.st_gid)->gr_name)) > biggest)
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

int					print_list_long(t_file *list, int width)
{
	t_file			*ptr;

	ptr = list;
	while (ptr)
	{
		ft_printf("%s %*d %-*s %-*s %*lld %s", ptr->infos.permissions, get_linkslen(list) + 1, ptr->stat.st_nlink, get_uidlen(list) + 1, getpwuid(ptr->stat.st_uid)->pw_name, get_grgidlen(list) + 1, getgrgid(ptr->stat.st_gid)->gr_name, get_biggestsize(list) + 1, ptr->stat.st_size, ptr->name);
		ft_putchar('\n');
		ptr = ptr->next;
	}
	(void)width;
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

int					print_list_column(t_file *list, int width)
{
	int				fileperline;
	int				lines;
	int				colcounter;
	t_file			*tmp;
	t_file			*tmp2;

	fileperline = width / (get_biggestnamelen(list) + 1);
	if (fileperline == 0)
		print_list_onepercolumn(list);
	else
	{
		lines = (get_listlen(list) / fileperline) + ((get_listlen(list) % fileperline == 0) ? 0 : 1);
		fileperline = (lines != 0) ? (get_listlen(list) / lines) : get_listlen(list);
		tmp = list;
		while (tmp != get_nnode(list, lines))
		{
			colcounter = 0;
			tmp2 = tmp;
			while (tmp2)
			{
				ft_printf("%-*s", get_biggestnamelen(list) + 1, tmp2->name);
				tmp2 = get_nnode(tmp2, lines);
				colcounter = ((colcounter + 1) >= fileperline) ? 0 : (colcounter + 1);
			}
			ft_printf("\n");
			tmp = tmp->next;
		}
	}
	return (1);
}

int				print_permissiondenied(t_file *file)
{
	ft_printf("ft_ls:\n%s: Permission denied\n", file->name);
	// la ou jappelle cette fonction, penser a l'erreur "directorz causes a cycle");
	return (1);
}

int				containadir(t_file *list)
{
	t_file		*ptr;

	ptr = list;
	while (ptr)
	{
		if (S_ISDIR(ptr->stat.st_mode))
			break;
		ptr = ptr->next;
	}
	if (ptr)
		return (1);
	return (0);
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
			if (isfirst == 0)
				isfirst = 1;
			else
				ft_putchar('\n');
			if (!(fill_dir(file, flags)))
			{
				print_permissiondenied(file);
				if (file->next)
					ft_putchar('\n');
			}
			else
			{
				ft_printf("%s:\n", file->path);
				print_filelist(&file->list, flags, width);
				clearlist(&file->list);
				if (containadir(file->list))
				{
					ft_putchar('\n');
					recursive(&file->list, flags, width);
				}
				freelist(&file->list);
			}
		}
		file = file->next;
	}
	return (1);
}

int				clearlist(t_file **list)
{
	t_file		*ptr;
	t_file		*tmp;

	ptr = *list;
	while (ptr)
	{
		if (!(S_ISDIR(ptr->stat.st_mode)))
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

int				print_firstdirlist(t_file **list, int flags, int width)
{
	t_file		*ptr;

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
