/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmlynarc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/14 14:30:39 by jmlynarc          #+#    #+#             */
/*   Updated: 2018/04/17 17:00:30 by jmlynarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		main(int ac, char **av)
{
	t_env		*env;
	t_map		*map;

	if (ac != 2)
		exit_usage();
	env = init_environnement();
	if (!(map = read_map_from(av[1])))
		exit_error(env);
	env->map = map;
	redraw_scene(env);
	mlx_hook(env->win_ptr, KEY_PRESS, KEY_PRESS_MASK, key_press, (void*)env);
	mlx_hook(env->win_ptr, KEY_RELEASE, KEY_RELEASE_MASK, key_release,
			(void*)env);
	mlx_loop_hook(env->mlx_ptr, no_event_loop, (void*)env);
	mlx_loop(env->mlx_ptr);
	return (0);
}
