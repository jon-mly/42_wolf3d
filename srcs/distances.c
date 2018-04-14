/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distances.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmlynarc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/14 14:30:08 by jmlynarc          #+#    #+#             */
/*   Updated: 2018/04/14 14:30:09 by jmlynarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

/*
 * If the coordinates are out of bounds, the case is hanlded as if there is a
 * wall.
 * (RQ : there should always be a wall on the bounds of the map)
 */

static int	wall_on_coord(int x, int y, t_env *env)
{
	if (x < 0 || x >= env->map.width || y < 0 || y >= env->map.height)
		return (1);
	return (env->map.map[y][x] == WALL);
}

/*
 * Correct the distance by mutliplying the result with cos(b), where
 * "b" is the angle between the center of the camera and the angle of the ray.
 */

static double	distance_between(t_camera camera, t_point intersect,
	double angle)
{
	double		squared_distance;
	double		square_root;

	squared_distance = pow((double)(camera.pos_x - intersect.x), 2) +
		pow((double)(camera.pos_y - intersect.y), 2);
	square_root = sqrt(squared_distance);
	return square_root; // * cos(angle - camera.angle);
}

/*
 * The angle that is passed in parameters shall be ABSOLUTE.
 */

double		min_horizontal_distance(t_env *env, double angle)
{
	t_point		intersect;
	int			y_multiplier;
	int			x_multiplier;
	int			dx;
	int			dy;

	y_multiplier = (sin(angle) < 0) ? 1 : -1;
	x_multiplier = (cos(angle) < 0) ? (-1) : 1;
	intersect.y = (env->camera.pos_y / TEXTURE_RES) * TEXTURE_RES +
		((y_multiplier < 0) ? -1 : TEXTURE_RES);
	intersect.x = env->camera.pos_x + floor((double)(env->camera.pos_y -
		intersect.y) / tan(angle));
	dy = y_multiplier * TEXTURE_RES;
	dx = floor((double)TEXTURE_RES / tan(angle));
	while (!wall_on_coord(intersect.x / TEXTURE_RES, intersect.y / TEXTURE_RES,
		env))
	{
		intersect.x += dx;
		intersect.y += dy;
	}
	printf("H.inter x: %d, y: %d ", intersect.x / TEXTURE_RES, intersect.y / TEXTURE_RES);
	return distance_between(env->camera, intersect, angle);
}

double		min_vertical_distance(t_env *env, double angle)
{
	t_point		intersect;
	int			y_multiplier;
	int			x_multiplier;
	int			dx;
	int			dy;

	y_multiplier = (sin(angle) < 0) ? 1 : -1;
	x_multiplier = (cos(angle) < 0) ? (-1) : 1;
	intersect.x = (env->camera.pos_x / TEXTURE_RES) * TEXTURE_RES +
		((x_multiplier > 0) ? TEXTURE_RES : -1);
	intersect.y = env->camera.pos_y + floor((double)(env->camera.pos_x -
		intersect.x) / tan(angle));
	dx = x_multiplier * TEXTURE_RES;
	dy = floor((double)TEXTURE_RES / tan(angle));
	while (!wall_on_coord(intersect.x / TEXTURE_RES, intersect.y / TEXTURE_RES,
		env))
	{
		intersect.x += dx;
		intersect.y += dy;
	}
	printf("V.inter x: %d, y: %d\n", intersect.x / TEXTURE_RES, intersect.y / TEXTURE_RES);
	return distance_between(env->camera, intersect, angle);
}
