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

static int		hit_x_wall(t_camera camera, double new_x_position, int **map)
{
	new_x_position += WALL_HIT_MARGIN * camera.direction.x;
	return (map[(int)(camera.position.y)][(int)new_x_position] == WALL);
}

static int		hit_y_wall(t_camera camera, double new_y_position, int **map)
{
	new_y_position += WALL_HIT_MARGIN * camera.direction.y;
	return (map[(int)new_y_position][(int)(camera.position.x)] == WALL);
}

static void		move_camera(t_env *env, t_cam_move side)
{
	double	new_x_position;
	double	new_y_position;
	int		multiplier;
	double	move;

	move = SPEED_PER_SEC * (double)(env->timer.frame_time);
	multiplier = (side == FORWARD) ? 1 : -1;
	new_x_position = env->camera.position.x + move * env->camera.direction.x *
		multiplier;
	new_y_position = env->camera.position.y + move * env->camera.direction.y *
		multiplier;
	if (hit_x_wall(env->camera, new_x_position, env->map->map))
		ft_putendl("Would collide with a wall X-AXIS");
	else
		env->camera.position.x = new_x_position;
	if (hit_y_wall(env->camera, new_y_position, env->map->map))
		ft_putendl("Would collide with a wall Y_AXIS");
	else
		env->camera.position.y = new_y_position;
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
	rotation = ROTATION_PER_SEC * (double)(env->timer.frame_time)
		* ((side == LEFT) ? 1 : -1);
	env->camera.angle += rotation;
	new_dir.x = old_dir.x * cos(rotation) - old_dir.y * sin(rotation);
	new_dir.y = old_dir.x * sin(rotation) + old_dir.y * cos(rotation);
	new_proj.x = old_proj.x * cos(rotation) - old_proj.y * sin(rotation);
	new_proj.y = old_proj.x * sin(rotation) + old_proj.y * cos(rotation);
	env->camera.direction = new_dir;
	env->camera.projection = new_proj;
}

int				move_camera_if_needed(t_env *env)
{
	if (env->camera.move == 0 && env->camera.rotate == 0)
		return (0);
	if (env->camera.rotate == 1 && env->camera.rotation_side == RIGHT)
		rotate_camera(env, RIGHT);
	else if (env->camera.rotate == 1 && env->camera.rotation_side == LEFT)
		rotate_camera(env, LEFT);
	if (env->camera.move == 1 && env->camera.move_side == FORWARD)
		move_camera(env, FORWARD);
	else if (env->camera.move == 1 && env->camera.move_side == BACKWARD)
		move_camera(env, BACKWARD);
	return (1);
}
