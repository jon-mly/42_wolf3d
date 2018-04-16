/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_drawing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmlynarc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/14 14:30:46 by jmlynarc          #+#    #+#             */
/*   Updated: 2018/04/14 14:30:47 by jmlynarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		fill_pixel(t_env *env, int x, int y, t_color color)
{
	int			i;
	if ((x < 0 || x >= env->img_width) ||
			(y < 0 || y >= env->img_height))
		return;
	i = (y * env->line_size) * 4 + x * 4;
	env->img_str[i] = color.b;
	env->img_str[i + 1] = color.g;
	env->img_str[i + 2] = color.r;
	env->img_str[i + 3] = color.a;
}

void		fill_pixel_value(t_env *env, int x, int y, int color_value)
{
	int			i;
	if ((x < 0 || x >= env->img_width) ||
			(y < 0 || y >= env->img_height))
		return;
	i = (y * env->line_size) * 4 + x * 4;
	env->img_str[i] = color_value;
}
