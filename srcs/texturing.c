/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texturing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmlynarc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/14 15:04:09 by jmlynarc          #+#    #+#             */
/*   Updated: 2018/07/17 17:08:39 by jmlynarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static t_texture	wall_texture_for(t_cardinal cardinal, t_env *env)
{
	if (cardinal == NORTH)
		return (env->textures[0]);
	else if (cardinal == EAST)
		return (env->textures[1]);
	else if (cardinal == WEST)
		return (env->textures[2]);
	else
		return (env->textures[3]);
}

/*
** Read a img file formatted as the images that are printed on the screen.
*/

static t_color		color_for_pixel(t_texture texture, int texture_x,
		int texture_y)
{
	t_color		color;
	int			index;

	color = (t_color){0, 0, 0, 0};
	if (texture_x < 0 || texture_x >= texture.width || texture_y < 0 ||
		texture_y >= texture.height)
		return (color);
	index = (texture_y * texture.line_size + texture_x) * 4;
	color.b = texture.img_str[index];
	color.g = texture.img_str[index + 1];
	color.r = texture.img_str[index + 2];
	color.a = texture.img_str[index + 3];
	return (color);
}

/*
** - texture : we get the texture that is to be applied accordingly to the
** side of the wall that is exposed to the camera.
** - wall_line is a value between 0 to 1 that represents the position of the
** hit point horizontally on the wall, 0 being full left, 0.5 right in the
** middle and 1 full right. (ray.direction gives the sign to the shift)
** - CAUTION : on the vertical side (where the y-axis was used), it is the
** x-axis that is used to do the calculation.
** - texture_line : gives the line of the texture, using the previous proportion
** applied on the width of the texture in pixels.
** - y : to avoid lag when very close to a wall, y is limited in the range
** [0, WIN_HEIGHT[, symetrically on both sides (hence the /2, -1 for bounds
** reasons).
** - texture_y : the vertical coordinate in the texture that should be applied
** on a given pixel. texture_y is included in [0, texture.height].
** cf. hand-written demo for proof
*/

void				apply_texture_on_line(int line, t_env *env, t_ray ray)
{
	t_texture		texture;
	double			wall_line;
	int				texture_line;
	int				texture_y;
	int				y;

	texture = wall_texture_for(ray.cardinal, env);
	wall_line = (ray.side == VERTICAL)
		? env->camera.position.x + ray.wall_distance * ray.direction.x
		: env->camera.position.y + ray.wall_distance * ray.direction.y;
	wall_line -= floor(wall_line);
	texture_line = (int)(wall_line * (double)(texture.width));
/*	if ((ray.side == HORIZONTAL && ray.direction.x > 0) ||
		(ray.side == VERTICAL && ray.direction.y < 0))
		texture_line = texture.width - texture_line - 1;
*/	y = fmax(-ray.wall_pixel_height / 2 + MID_HEIGHT - 1, 0);
	while (++y < fmin(ray.wall_pixel_height / 2 + MID_HEIGHT, WIN_HEIGHT))
	{
		texture_y = (((y * 2 - env->win_height + ray.wall_pixel_height)
					* texture.height) / ray.wall_pixel_height) / 2;
		fill_pixel(env, line, y, color_for_pixel(texture, texture_line,
			texture_y));
	}
}
