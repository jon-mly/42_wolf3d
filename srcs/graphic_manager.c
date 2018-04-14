/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_manager.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmlynarc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/14 14:30:32 by jmlynarc          #+#    #+#             */
/*   Updated: 2018/04/14 14:30:32 by jmlynarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void		print_debug(t_env *env)
{
	int cam_x = env->camera.pos_x;
	int cam_y = env->camera.pos_y;

	printf("-----\n");
	printf("CAMERA - x : %d (%d), y : %d (%d)\n", cam_x, cam_x / TEXTURE_RES, cam_y, cam_y / TEXTURE_RES);
	printf("ANGLE : %.2f\n", env->camera.angle * 180.0 / M_PI);
}

void	redraw_scene(t_env *env)
{
	int		column;
	int			bpp;
	int			s_l;
	int			endian;

	print_debug(env);
	if (env->img_ptr)
		mlx_destroy_image(env->mlx_ptr, env->img_ptr);
	if (!(env->img_ptr = mlx_new_image(env->mlx_ptr, env->win_width, env->win_height)))
		return;
	env->img_width = WIN_WIDTH;
	env->img_height = WIN_HEIGHT;
	env->img_str = (unsigned char *)(mlx_get_data_addr(env->img_ptr, &bpp, &s_l, &endian));
	env->line_size = s_l / 4;
	column = -1;
	while (++column < WIN_WIDTH)
		cast_ray(column, env);
	mlx_put_image_to_window((void *)env, env->win_ptr, env->img_ptr, 0, 0);
}
