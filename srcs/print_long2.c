/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_long2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/29 22:13:20 by toliver           #+#    #+#             */
/*   Updated: 2018/08/29 22:14:20 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int					print_blksize(t_file *list)
{
	t_file			*ptr;
	int				totalsize;

	ptr = list;
	totalsize = 0;
	while (ptr)
	{
		totalsize += ptr->stat.st_blocks;
		ptr = ptr->next;
	}
	ft_printf("total %d\n", totalsize);
	return (1);
}
