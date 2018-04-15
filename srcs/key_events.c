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

static void		move_camera(t_env *env, t_cam_move side)
{
	double	new_x_position;
	double	new_y_position;
	int		multiplier;

	multiplier = (side == FORWARD) ? 1 : -1;
	new_x_position = env->camera.position.x + 0.2 * env->camera.direction.x *
		multiplier;
	new_y_position = env->camera.position.y + 0.2 * env->camera.direction.y *
		multiplier;
	if (env->map->map[(int)new_y_position][(int)new_x_position] == WALL)
		ft_putendl("Would collide with a wall");
	else
	{
		env->camera.position.x = new_x_position;
		env->camera.position.y = new_y_position;
	}
}

static void		rotate_camera(t_env *env, t_cam_rotation side)
{
	double		rotation;
	t_vector	old_dir;
	t_vector	new_dir;
	t_vector	old_proj;
	t_vector	new_proj;

	old_dir = env->camera.direction;
	old_proj = env->camera.projection;
	rotation = ROTATION_ANGLE * ((side == LEFT) ? 1 : -1);
	env->camera.angle += rotation;
	new_dir.x = old_dir.x * cos(rotation) - old_dir.y * sin(rotation);
	new_dir.y = old_dir.x * sin(rotation) + old_dir.y * cos(rotation);
	new_proj.x = old_proj.x * cos(rotation) - old_proj.y * sin(rotation);
	new_proj.y = old_proj.x * sin(rotation) + old_proj.y * cos(rotation);
	env->camera.direction = new_dir;
	env->camera.projection = new_proj;
}

static int		handle_key(int key, t_env *env)
{
	if (key == KEY_ARROW_RIGHT)
		rotate_camera(env, RIGHT);
	else if (key == KEY_ARROW_LEFT)
		rotate_camera(env, LEFT);
	else if (key == KEY_ARROW_UP)
		move_camera(env, FORWARD);
	else if (key == KEY_ARROW_DOWN)
		move_camera(env, BACKWARD);
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
