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
	double cam_x = env->camera.position.x;
	double cam_y = env->camera.position.y;

	printf("-----\n");
	printf("CAMERA - x : %.3f (%d), y : %.3f (%d)\n", cam_x, (int)cam_x, cam_y, (int)cam_y);
	printf("ANGLE : %.2f\n", env->camera.angle * 180.0 / M_PI);
}

static int		should_redraw(t_env *env)
{
	env->timer.previous_time = env->timer.current_time;
	env->timer.current_time = clock();
	if (env->timer.next_frame > env->timer.current_time)
		return (0);
	env->timer.frame_time = (double)(env->timer.current_time
		- env->timer.previous_time) / (double)CLOCKS_PER_SEC;
	env->timer.next_frame = env->timer.current_time + (CLOCKS_PER_SEC / 150);
	return ((move_camera_if_needed(env)) || env->img_ptr == NULL);
}

void			redraw_scene(t_env *env)
{
	int		column;
	int			bpp;
	int			s_l;
	int			endian;

	if (!(should_redraw(env)))
		return;
	if (!(env->img_ptr))
	{
		if (!(env->img_ptr = mlx_new_image(env->mlx_ptr, env->win_width, env->win_height)))
			return;
		env->img_width = WIN_WIDTH;
		env->img_height = WIN_HEIGHT;
		env->img_str = (unsigned char *)(mlx_get_data_addr(env->img_ptr, &bpp, &s_l, &endian));
		env->line_size = s_l / 4;
	}
/*
	if (env->img_ptr)
		mlx_destroy_image(env->mlx_ptr, env->img_ptr);
	if (!(env->img_ptr = mlx_new_image(env->mlx_ptr, env->win_width, env->win_height)))
		return;
	env->img_width = WIN_WIDTH;
	env->img_height = WIN_HEIGHT;
	env->img_str = (unsigned char *)(mlx_get_data_addr(env->img_ptr, &bpp, &s_l, &endian));
	env->line_size = s_l / 4;
*/	
	column = -1;
	while (++column < WIN_WIDTH)
		cast_ray(column, env);
	mlx_put_image_to_window((void *)env, env->win_ptr, env->img_ptr, 0, 0);
}
