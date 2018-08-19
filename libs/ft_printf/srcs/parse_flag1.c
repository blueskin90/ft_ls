/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_flag1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 19:30:26 by toliver           #+#    #+#             */
/*   Updated: 2018/03/21 19:32:06 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int				parse_minusflag(t_env *env, t_arg *arg)
{
	env->str++;
	arg->flags |= 32;
	return (1);
}

int				parse_plusflag(t_env *env, t_arg *arg)
{
	env->str++;
	arg->flags |= 16;
	return (1);
}

int				parse_zeroflag(t_env *env, t_arg *arg)
{
	env->str++;
	arg->flags |= 8;
	return (1);
}

int				parse_spaceflag(t_env *env, t_arg *arg)
{
	env->str++;
	arg->flags |= 4;
	return (1);
}

int				parse_hashflag(t_env *env, t_arg *arg)
{
	env->str++;
	arg->flags |= 2;
	return (1);
}
