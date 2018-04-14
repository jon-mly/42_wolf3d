/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmlynarc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/14 14:30:14 by jmlynarc          #+#    #+#             */
/*   Updated: 2018/04/14 16:01:12 by jmlynarc         ###   ########.fr       */
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
}

static void			setup_camera(t_env *env)
{
	t_camera	camera;

	camera.position.x = 3.5 * TEXTURE_RES;
	camera.position.y = 3.5 * TEXTURE_RES;
	camera.angle = M_PI / 2;
	camera.direction.x = 0;
	camera.direction.y = -1;
	camera.projection.x = FOV;
	camera.projection.y = 0;
	camera.height = TEXTURE_RES / 2;
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
	setup_environnement(env);
	setup_camera(env);
	return (env);
}

