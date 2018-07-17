/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmlynarc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/14 16:09:33 by jmlynarc          #+#    #+#             */
/*   Updated: 2018/07/17 17:07:30 by jmlynarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

/*
** Creates the ray with the data needed to calculate the distance between the
** camera and the closest wall.
** - projection_x: value between -1 and +1 that defines the vertical proportion
** of the projection plane we're in. The vector projection is defined from the
** center point of the screen to the point at the right of the screen. Hence
** a -1 to 1 value.
** - direction is set up as a variation of the camera's direction. Direction is
** NOT a unit vector => avoid fish eye effect without further calculation.
** - map_position starts on the camera's position.
** - deltas are calculated for further calculations.
** - side_shifts are initially calculated to reach the first x/y border. Hence,
** it is a proportion of deltas, the proportion being the distance between
** the camera and the first line, which is between 0 and 1.
*/

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

/*
** Starting from the first x & y axis encountered from the camera in the
** direction calculated for the ray : algorithm to find the closest distance
** between the camera and the first walli, either vertically or horizontally,
** as refered by the side_shifts values.
** - deltas being the quantity of ray.direction to apply to reach the next
** x or y axis, side_shift (which is not a vector) tracks the proportion of
** ray.direction that should be applied to reach the intersection between the
** axis from the camera.
** - x/y_direction are either +1 or -1. Are applied to move block by block in
** the map (intersection to intersection).
*/

static t_ray		closest_distance_to_wall(t_ray ray, t_env *env)
{
	while (ray.surface == EMPTY
			&& position_is_in_bounds(ray.map_position, *(env->map)))
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
		if (env->map->map[ray.map_position.y][ray.map_position.x] != EMPTY)
			ray.surface = WALL;
	}
	if (ray.side == VERTICAL)
		ray.cardinal = (ray.direction.y < 0) ? NORTH : SOUTH;
	else
		ray.cardinal = (ray.direction.x < 0) ? EAST : WEST;
	return (ray);
}

/*
** To get a correct rendering and avoid a curved wall, only the vertical or
** hroizontal distance is being calculated (as if the wall parallel to The
** projection vector).
** The value is then divided by the direction. It has two effects :
** - the difference between map_position and camera can result in a negative
** value that is cancelled with direction's sign.
** - ray.direction is NOT a unit vector : longer on the sides than on the
** center. It corrects the fish eye effect without modifying the value with
** by a trigonometric factor.
** Wall_distance being an arbitrary value, it is admitted that if it is equal
** to 1, the wall will take the whole screen (dividing the height in pixel By
** 1).
*/

static t_ray		calculate_wall_height(t_ray ray, t_env *env)
{
	if (ray.side == HORIZONTAL)
		ray.wall_distance = ((double)(ray.map_position.x) -
			env->camera.position.x + ((ray.x_direction < 0) ? 1 : 0)) /
			ray.direction.x;
	else
	{
		ray.wall_distance = ((double)(ray.map_position.y) -
			env->camera.position.y + ((ray.y_direction < 0) ? 1 : 0)) /
			ray.direction.y;
	}
	ray.wall_pixel_height = (int)((double)(env->win_height) /
		ray.wall_distance);
	return (ray);
}

void				cast_ray(int column, t_env *env)
{
	t_ray		ray;

	ray = init_ray(column, env);
	ray = closest_distance_to_wall(ray, env);
	ray = calculate_wall_height(ray, env);
	draw_column(column, env, ray);
}
