/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmlynarc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/14 14:30:28 by jmlynarc          #+#    #+#             */
/*   Updated: 2018/06/22 15:47:08 by jmlynarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		exit_usage(void)
{
	ft_putendl("Usage : ./wolf3d [map file path]");
	exit(0);
}

void		exit_error(t_env *env)
{
	ft_putendl("An error has occured");
	deinit_env(env);
	exit(0);
}

void		exit_normally(t_env *env)
{
	deinit_env(env);
	exit(0);
}
