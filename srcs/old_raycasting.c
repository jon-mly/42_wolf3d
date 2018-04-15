/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmlynarc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/14 14:30:50 by jmlynarc          #+#    #+#             */
/*   Updated: 2018/04/14 14:39:50 by jmlynarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void		draw_ceiling(int x, int y, t_env *env)
{
	t_color		color;

	color.r = 100;
	color.g = 200;
	color.b = 255;
	color.a = 1;
	fill_pixel(env, x, y, color);
}

static void		draw_floor(int x, int y, t_env *env)
{
t_color		color;

	color.r = 50;
	color.g = 100;
	color.b = 200;
	color.a = 1;
	fill_pixel(env, x, y, color);
}

static void		draw_wall(int x, int y, t_env *env, t_cardinal cardinal)
{
	t_color		color;
	int			color_value;

	if (cardinal == NORTH || cardinal == SOUTH)
		color_value = 100;
	else if (cardinal == EAST)
		color_value = 130;
	else
		color_value = 70;
	color.r = color_value;
	color.g = color_value;
	color.b = color_value;
	color.a = 1;
	fill_pixel(env, x, y, color);
}

/*
 * Cast a ray on the pixel column pointed by index.
 * Will also draw the line on the current image.
 * The wall height is given in pixel.
 */

void			cast_ray(int index, t_env *env)
{
	double		angle;
	double		horizontal_distance;
	double		vertical_distance;
	int			wall_distance;
	int			wall_height_projection;

	angle = env->camera.angle - (double)(index - MID_WIDTH) * (FOV) / (double)WIN_WIDTH;
	horizontal_distance = min_horizontal_distance(env, angle);
	vertical_distance = min_vertical_distance(env, angle);
	wall_distance = horizontal_distance;//floor(fmin(horizontal_distance, vertical_distance));
	printf("%.1f angle, %.1f vert., %.1f hor., chosen = %d\n", (angle * 180.0) / M_PI, horizontal_distance, vertical_distance, wall_distance);
	wall_height_projection = floor((double)(WALL_HEIGHT * SCREEN_DISTANCE) /
		(double)wall_distance);
	draw_column(index, env, wall_height_projection,
		cardinal_for_wall(horizontal_distance, vertical_distance, angle));
}

