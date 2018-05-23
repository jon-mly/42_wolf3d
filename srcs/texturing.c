/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texturing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmlynarc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/14 15:04:09 by jmlynarc          #+#    #+#             */
/*   Updated: 2018/05/23 11:44:59 by jmlynarc         ###   ########.fr       */
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
	if ((ray.side == HORIZONTAL && ray.direction.x > 0) ||
		(ray.side == VERTICAL && ray.direction.y < 0))
		texture_line = texture.width - texture_line - 1;
	y = -ray.wall_pixel_height / 2 + MID_HEIGHT - 1;
	while (++y <= ray.wall_pixel_height / 2 + MID_HEIGHT)
	{
		texture_y = (((y * 256 - env->win_height * 128 + ray.wall_pixel_height
		* 128) * texture.height) / ray.wall_pixel_height) / 256;
		fill_pixel(env, line, y, color_for_pixel(texture, texture_line,
					texture_y));
	}
}
