/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_arg2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 17:13:55 by toliver           #+#    #+#             */
/*   Updated: 2018/06/06 17:14:07 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int				get_int(t_env *env, t_arg *arg)
{
	arg->argument.i = va_arg(env->arg, int);
	return (1);
}

int				get_char(t_env *env, t_arg *arg)
{
	arg->argument.i = (char)va_arg(env->arg, int);
	return (1);
}

int				get_short(t_env *env, t_arg *arg)
{
	arg->argument.si = (short int)va_arg(env->arg, int);
	return (1);
}

int				get_long(t_env *env, t_arg *arg)
{
	arg->argument.li = va_arg(env->arg, long int);
	return (1);
}

int				get_longlong(t_env *env, t_arg *arg)
{
	arg->argument.lli = va_arg(env->arg, long long int);
	return (1);
}
