/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 15:32:16 by toliver           #+#    #+#             */
/*   Updated: 2018/06/06 21:54:55 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void							env_init(t_env *env, const char *str)
{
	env->str = str;
	env->strcopy = str;
	env->buffilasttoken = 0;
	env->buffi = 0;
	env->lastparam = 0;
	env->printflen = 0;
	env_ptrarrayinit(env);
	env_getarrayinit(env);
	env->null[0] = '(';
	env->null[1] = 'n';
	env->null[2] = 'u';
	env->null[3] = 'l';
	env->null[4] = 'l';
	env->null[5] = ')';
	env->null[6] = '\0';
}

int								ft_printf(const char *str, ...)
{
	t_env						env;

	if (str == NULL)
	{
		write(1, "Gare au segfault !\n", 35);
		return (-1);
	}
	env_init(&env, str);
	va_start(env.arg, str);
	if (parse_string(&env) == -1)
	{
		buff_flush(&env);
		return (-1);
	}
	buff_flush(&env);
	return (env.printflen);
}
