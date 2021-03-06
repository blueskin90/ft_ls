/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_arg1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 00:27:04 by toliver           #+#    #+#             */
/*   Updated: 2018/06/06 17:14:36 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int				get_intmaxt(t_env *env, t_arg *arg)
{
	arg->argument.imax = va_arg(env->arg, intmax_t);
	return (1);
}

int				get_sizet(t_env *env, t_arg *arg)
{
	arg->argument.siz = va_arg(env->arg, size_t);
	return (1);
}

int				get_ptrdifft(t_env *env, t_arg *arg)
{
	arg->argument.ptd = va_arg(env->arg, ptrdiff_t);
	return (1);
}

int				get_ldouble(t_env *env, t_arg *arg)
{
	arg->argument.ld = va_arg(env->arg, long double);
	return (1);
}

int				get_double(t_env *env, t_arg *arg)
{
	arg->argument.d = va_arg(env->arg, double);
	return (1);
}
