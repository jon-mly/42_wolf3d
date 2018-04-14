/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmlynarc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/14 14:30:39 by jmlynarc          #+#    #+#             */
/*   Updated: 2018/04/14 14:30:40 by jmlynarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	print_map(t_map map)
{
	ft_putendl("MAP :");
	int height = map.height;
	int width = map.width;
	printf("height = %d and width = %d\n", height, width);
	int i = -1;
	int j;
	while (++i < height)
	{
		j = -1;
		while (++j < width)
		{
			ft_putnbr(map.map[i][j]);
			ft_putchar(' ');
		}
		ft_putchar('\n');
	}
}

int		main(int ac, char **av)
{
	t_env		*env;
	t_map		*map;

	if (ac != 2)
		exit_usage();
	env = init_environnement();
	if (!(map = read_map_from(av[1])))
		exit_error(env);
	env->map = *map;
	print_map(*map);
	redraw_scene(env);
	mlx_key_hook(env->win_ptr, deal_with_key, (void*)env);
	mlx_loop(env->mlx_ptr);
	return (0);
}
