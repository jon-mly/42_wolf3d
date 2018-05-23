/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deinit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmlynarc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 16:58:06 by jmlynarc          #+#    #+#             */
/*   Updated: 2018/05/23 11:46:05 by jmlynarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void		deinit_map(t_map *map)
{
	int		**grid;
	int		counter;

	grid = map->map;
	counter = -1;
	while (++counter < map->height)
		free(grid[counter]);
	ft_memdel((void**)(&grid));
	ft_memdel((void**)(&map));
}

static void		deinit_textures(t_texture *textures, int count)
{
	int				counter;
	t_texture		texture;

	counter = -1;
	if (textures)
	{
		while (++counter < count)
			texture = textures[count];
		ft_memdel((void**)(&textures));
	}
}

void			deinit_env(t_env *env)
{
	deinit_map(env->map);
	deinit_textures(env->textures, env->textures_count);
	if (env->img_ptr && env->mlx_ptr)
		mlx_destroy_image(env->mlx_ptr, env->img_ptr);
	if (env->win_ptr && env->mlx_ptr)
		mlx_destroy_window(env->mlx_ptr, env->win_ptr);
	ft_memdel((void**)(&(env->mlx_ptr)));
	ft_memdel((void**)(&env));
}
