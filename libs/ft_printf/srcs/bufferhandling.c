/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bufferhandling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 20:41:34 by toliver           #+#    #+#             */
/*   Updated: 2018/05/17 02:21:04 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

#include <stdio.h>

void			buff_check(t_env *env)
{
	if (env->buffi == BUFFSIZE)
	{
		env->buffilasttoken = env->buffi;
		buff_flush(env);
	}
}

void			buff_flush(t_env *env)
{
	env->printflen += env->buffilasttoken;
	write(1, env->buff, env->buffilasttoken);
	env->buffi = 0;
	env->buffilasttoken = 0;
}
