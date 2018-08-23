/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/19 23:28:42 by toliver           #+#    #+#             */
/*   Updated: 2018/08/23 16:56:14 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int			main(int argc, char **argv)
{
	t_param	env;

	envinit(&env);
	parsing(argc, argv, &env);
	first_check(&env);
	listorder(&env.list, env.flags);
	return (1);
}
