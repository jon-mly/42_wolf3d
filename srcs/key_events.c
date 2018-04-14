/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmlynarc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/14 14:30:35 by jmlynarc          #+#    #+#             */
/*   Updated: 2018/04/14 14:30:36 by jmlynarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void		move_camera(t_env *env, int forward)
{
	double	angle;
	int		multiplier;

	angle = env->camera.angle;
	multiplier = (forward) ? 1 : -1;
	env->camera.pos_x += 10 * cos(angle) * multiplier;
	env->camera.pos_y += 10 * sin(angle) * multiplier * (-1);
}

static int		handle_key(int key, t_env *env)
{
	if (key == KEY_ARROW_RIGHT)
		env->camera.angle += ROTATION_ANGLE;
	else if (key == KEY_ARROW_LEFT)
		env->camera.angle -= ROTATION_ANGLE;
	else if (key == KEY_ARROW_UP)
		move_camera(env, 1);
	else if (key == KEY_ARROW_DOWN)
		move_camera(env, 0);
	else
		return (0);
	redraw_scene(env);
	return (1);
}

int				deal_with_key(int key, void *param)
{
	t_env	*env;

	env = (t_env*)param;
	if (key == KEY_ESC)
		exit_normally(env);
	else
		handle_key(key, env);
	return (0);
}
