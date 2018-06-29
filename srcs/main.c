/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmlynarc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/14 14:30:39 by jmlynarc          #+#    #+#             */
/*   Updated: 2018/06/29 14:56:19 by jmlynarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void		set_up_hooks(t_env *env)
{
	mlx_hook(env->win_ptr, KEY_PRESS, KEY_PRESS_MASK, key_press, (void*)env);
	mlx_hook(env->win_ptr, KEY_RELEASE, KEY_RELEASE_MASK, key_release,
			(void*)env);
	mlx_hook(env->win_ptr, WIN_CROSS, NO_MASK, event_hook, (void*)env);
	mlx_loop_hook(env->mlx_ptr, no_event_loop, (void*)env);
	mlx_loop(env->mlx_ptr);
}

int				main(int ac, char **av)
{
	t_env		*env;
	t_map		*map;

	if (ac != 2)
		exit_usage();
	env = init_environnement();
	if (!(map = read_map_from(av[1])))
		exit_error(env, "Map could not be created");
	env->map = map;
	if (!map_surrounded_by_walls(*(env->map)))
		exit_error(env, "Map should be surrounded by walls");
	redraw_scene(env);
	set_up_hooks(env);
	return (0);
}
