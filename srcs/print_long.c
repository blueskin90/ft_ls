/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_long.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/29 22:12:22 by toliver           #+#    #+#             */
/*   Updated: 2018/08/29 22:15:42 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int					print_list_long(t_file *list, int width, int flags)
{
	t_file			*ptr;

	ptr = list;
	if (ptr)
		print_blksize(list);
	while (ptr)
	{
		ft_printf("%.10s %*d", ptr->infos.permissions, get_linkslen(list) + 1,
				ptr->stat.st_nlink);
		print_users(list, ptr, flags);
		print_size(get_biggestsize(list) + 1, ptr);
		print_time(list, ptr);
		ft_printf(" %s", ptr->name);
		if (ptr->infos.permissions[0] == 'l')
			print_link(ptr);
		ft_putchar('\n');
		ptr = ptr->next;
	}
	(void)width;
	return (1);
}

int					print_users(t_file *list, t_file *ptr, int flags)
{
	if (!(flags & G_FLAG))
	{
		if (getpwuid(ptr->stat.st_uid) != NULL)
			ft_printf(" %-*s", get_uidlen(list) + 1,
					getpwuid(ptr->stat.st_uid)->pw_name);
		else
			ft_printf(" %-*d", get_uidlen(list) + 1, ptr->stat.st_uid);
	}
	if (getgrgid(ptr->stat.st_gid) != NULL)
		ft_printf(" %-*s", get_grgidlen(list) + 1,
				getgrgid(ptr->stat.st_gid)->gr_name);
	else
		ft_printf("%-*d", get_grgidlen(list) + 1, ptr->stat.st_gid);
	return (1);
}

int					print_time(t_file *list, t_file *ptr)
{
	ft_printf(" %.3s", ctime(&ptr->stat.st_ctimespec.tv_sec) + 4);
	ft_printf(" %*d", get_biggestday(list),
			ft_atoi(ctime(&ptr->stat.st_ctimespec.tv_sec) + 7));
	ft_printf(" %.5s", ctime(&ptr->stat.st_ctimespec.tv_sec) + 11);
	return (1);
}

int					print_size(int biggest, t_file *ptr)
{
	if (ptr->infos.permissions[0] == 'c' || ptr->infos.permissions[0] == 'b')
		ft_printf("%u, %u", major(ptr->stat.st_rdev), minor(ptr->stat.st_rdev));
	else
		ft_printf("%*lld", biggest, ptr->stat.st_size);
	return (1);
}

int					print_link(t_file *ptr)
{
	char			path[PATH_MAX + 1];
	int				readret;

	if ((readret = readlink(ptr->path, path, PATH_MAX)) == -1)
		return (-1);
	path[readret] = '0';
	ft_printf(" -> %s", path);
	return (1);
}
