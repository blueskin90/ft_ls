/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_move.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/29 22:01:58 by toliver           #+#    #+#             */
/*   Updated: 2018/08/29 22:02:55 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int			movenode(t_file **listfrom, t_file *filetomove, t_file **listto)
{
	delnode(listfrom, filetomove);
	addnode(listto, filetomove);
	return (1);
}

int			movenodefirst(t_file **from, t_file *filetomove, t_file **to)
{
	delnode(from, filetomove);
	addfirstnode(to, filetomove);
	return (1);
}
