/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_drawing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmlynarc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 16:58:55 by jmlynarc          #+#    #+#             */
/*   Updated: 2018/07/17 15:13:23 by jmlynarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		draw_ceiling(int x, int y, t_env *env)
{
	t_color		color;

	color.r = 100;
	color.g = 200;
	color.b = 255;
	color.a = 1;
	fill_pixel(env, x, y, color);
}

void		draw_floor(int x, int y, t_env *env)
{
	t_color		color;

	color.r = 50;
	color.g = 100;
	color.b = 200;
	color.a = 1;
	fill_pixel(env, x, y, color);
}

/*
** FIXME: may be unused
*/

void		draw_wall(int x, int y, t_env *env, t_cardinal cardinal)
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
** Knowing the number of pixel that should be attributed to the wall, and that
** the wall is centered in the screen (choie made when developing), we know
** which pixels are to be colored for the floor or the ceiling, which are drawn
** statically.
** cf. texturing.c for the texturing algorithm.
*/

void		draw_column(int index, t_env *env, t_ray ray)
{
	int		line;

	line = -1;
	apply_texture_on_line(index, env, ray);
	while (++line < WIN_HEIGHT)
	{
		if (line < -ray.wall_pixel_height / 2 + MID_HEIGHT)
			draw_ceiling(index, line, env);
		else if (line >= ray.wall_pixel_height / 2 + MID_HEIGHT)
			draw_floor(index, line, env);
	}
}
