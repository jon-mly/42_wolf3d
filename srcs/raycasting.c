/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmlynarc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/14 16:09:33 by jmlynarc          #+#    #+#             */
/*   Updated: 2018/04/14 17:18:54 by jmlynarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static t_ray		init_ray(int column, t_env *env)
{
	t_ray		ray;
	double		projection_x;

	projection_x = 2 * (double)column / (double)env->win_width - 1;
	ray.direction.x = env->camera.direction.x + env->camera.plane.x
		* projection_x;
	ray.direction.y = env->camera.direction.y + env->camera.plane.y
		* projection_x;
}

void				cast_ray(int column, t_env *env)
{
	t_ray		ray;

	ray = init_ray(column, env);
}
