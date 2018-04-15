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
	ray.direction.x = env->camera.direction.x + env->camera.projection.x
		* projection_x;
	ray.direction.y = env->camera.direction.y + env->camera.projection.y
		* projection_x;
	ray.map_position.x = (int)(env->camera.position.x);
	ray.map_position.y = (int)(env->camera.position.y);
	ray.delta_x = fabs(1 / ray.direction.x);
	ray.delta_y = fabs(1 / ray.direction.y);
	ray.surface = EMPTY;
	ray.x_direction = (ray.direction.x < 0) ? -1 : 1;
	ray.side_shift.x = (ray.direction.x < 0)
		? (env->camera.position.x - (double)(ray.map_position.x)) * ray.delta_x
		: ((double)(ray.map_position.x) + 1.0 - env->camera.position.x) *
			ray.delta_x;
	ray.y_direction = (ray.direction.y < 0) ? -1 : 1;
	ray.side_shift.y = (ray.direction.y < 0)
		? (env->camera.position.y - (double)(ray.map_position.y)) * ray.delta_y
		: ((double)(ray.map_position.y) + 1.0 - env->camera.position.y) *
			ray.delta_y;
	return (ray);
}

static t_ray		digital_differential_analysis(t_ray ray, t_env *env)
{
	while (ray.surface == EMPTY)
	{
		if (ray.side_shift.x < ray.side_shift.y)
		{
			ray.side_shift.x += ray.delta_x;
			ray.map_position.x += (int)(ray.x_direction);
			ray.side = HORIZONTAL;
		}
		else
		{
			ray.side_shift.y += ray.delta_y;
			ray.map_position.y += (int)(ray.y_direction);
			ray.side = VERTICAL;
		}
		if (env->map.map[ray.map_position.y][ray.map_position.x] != EMPTY)
			ray.surface = WALL;
	}
	if (ray.side == VERTICAL)
		ray.cardinal = (ray.direction.y < 0) ? NORTH : SOUTH;
	else
		ray.cardinal = (ray.direction.x < 0) ? EAST : WEST;
	return (ray);
}

static t_ray		calculate_wall_height(t_ray ray, t_env *env)
{
	if (ray.side == HORIZONTAL)
		ray.wall_distance = ((double)(ray.map_position.x) -
			env->camera.position.x + (1 - ray.x_direction) / 2) /
			ray.direction.x;
	else
		ray.wall_distance = ((double)(ray.map_position.y) -
			env->camera.position.y + (1 - ray.y_direction) / 2) /
			ray.direction.y;
	ray.wall_pixel_height = (int)((double)(env->win_height) /
		ray.wall_distance);
	return (ray);
}

void				cast_ray(int column, t_env *env)
{
	t_ray		ray;

	ray = init_ray(column, env);
	ray = digital_differential_analysis(ray, env);
	ray = calculate_wall_height(ray, env);
	draw_column(column, env, ray.wall_pixel_height, ray.cardinal);
}
