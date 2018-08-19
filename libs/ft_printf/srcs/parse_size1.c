/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_size1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/22 18:10:03 by toliver           #+#    #+#             */
/*   Updated: 2018/06/06 21:53:26 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void			arg_parse(t_env *env, t_arg *arg)
{
	(void)arg;
	(void)env;
}

/*
** PENSER A GERER le $ dans la suivante
*/

int				get_arg(t_env *env, t_arg *arg)
{
	if (env->get_arg[arg->cat][arg->length] == NULL)
		return (env->get_arg[arg->cat][0](env, arg));
	else
		return (env->get_arg[arg->cat][arg->length](env, arg));
}

int				parse_dsize(t_env *env, t_arg *arg)
{
	arg->cat = 0;
	arg->type = 1;
	flags_cleanup(arg);
	get_arg(env, arg);
	arg_parse(env, arg);
	buff_fillint(env, arg);
	env->str++;
	return (0);
}

int				parse_bigdsize(t_env *env, t_arg *arg)
{
	arg->cat = 0;
	arg->type = 1;
	arg->length = (arg->length < 3) ? 3 : arg->length;
	flags_cleanup(arg);
	get_arg(env, arg);
	arg_parse(env, arg);
	buff_fillint(env, arg);
	env->str++;
	return (0);
}

int				parse_osize(t_env *env, t_arg *arg)
{
	arg->cat = 0;
	arg->type = 2;
	flags_cleanup(arg);
	get_arg(env, arg);
	arg_parse(env, arg);
	buff_filloct(env, arg);
	env->str++;
	return (0);
}
