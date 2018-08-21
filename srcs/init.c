/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/20 17:40:25 by toliver           #+#    #+#             */
/*   Updated: 2018/08/20 17:41:24 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int					envinit(t_param *env)
{
	struct winsize	w;
	if ((ioctl(0, TIOCGWINSZ, &w)) == -1)
	{
		ft_putstr_fd("Couldn't get the size of the terminal\n", 2);
		exit(1);
	}
	env->width = w.ws_col;
	env->flags = 0;
	env->list = NULL;
	env->errorlist = NULL;
	return (1);
}
