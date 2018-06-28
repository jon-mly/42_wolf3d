/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmlynarc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/14 14:30:14 by jmlynarc          #+#    #+#             */
/*   Updated: 2018/06/28 16:07:34 by jmlynarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void			setup_environnement(t_env *env)
{
	env->mlx_ptr = mlx_init();
	env->win_ptr = mlx_new_window(env->mlx_ptr, WIN_WIDTH, WIN_HEIGHT,
		"Wolf 3D");
	env->win_width = WIN_WIDTH;
	env->win_height = WIN_HEIGHT;
	if (env->mlx_ptr == NULL || env->win_ptr == NULL)
		exit_error(env);
	env->timer.previous_time = clock();
	env->timer.current_time = clock();
	env->timer.next_frame = clock() + (CLOCKS_PER_SEC / 150);
}

static void			setup_camera(t_env *env)
{
	t_camera	camera;

	camera.position.x = 3.5;
	camera.position.y = 3.5;
	camera.angle = M_PI / 2;
	camera.direction.x = 0;
	camera.direction.y = -1;
	camera.direction = normalize_vector(camera.direction);
	camera.projection.x = FOV;
	camera.projection.y = 0;
	camera.height = TEXTURE_RES / 2;
	camera.move = 0;
	camera.rotate = 0;
	env->camera = camera;
}

t_env				*init_environnement(void)
{
	t_env		*env;

	if (!(env = (t_env*)malloc(sizeof(t_env))))
		return (NULL);
	env->mlx_ptr = NULL;
	env->win_ptr = NULL;
	env->img_ptr = NULL;
	env->img_str = NULL;
	env->textures = NULL;
	env->textures_count = 0;
	env->map = NULL;
	setup_environnement(env);
	setup_camera(env);
	init_textures(env);
	return (env);
}
