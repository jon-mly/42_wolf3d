/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmlynarc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/14 14:30:28 by jmlynarc          #+#    #+#             */
/*   Updated: 2018/04/14 14:30:29 by jmlynarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		exit_usage(void)
{
	ft_putendl("wolf3d [map file path]");
	exit(0);
}

void		exit_error(t_env *env)
{
	ft_putendl("An error has occured");
	// TODO: deinit env
	exit(0);
}

void		exit_normally(t_env *env)
{
	// TODO: deinit env
	exit(0);
}
