/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deinit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmlynarc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 16:58:06 by jmlynarc          #+#    #+#             */
/*   Updated: 2018/04/17 17:05:07 by jmlynarc         ###   ########.fr       */
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
	ft_putendl("lines are freed");
	ft_memdel((void**)(&grid));
	ft_putendl("grid is freed");
	ft_memdel((void**)(&map));
	ft_putendl("map is freed");
}

static void		deinit_textures(t_texture *textures, int count, t_env *env)
{
	int				counter;
	t_texture		texture;

	counter = -1;
	if (textures)
	{
		while (++counter < count)
		{
			texture = textures[count];
			printf("%p\n", texture.img_ptr);
			ft_putendl("Is reached");
			ft_putendl("texture image freed");
			ft_putendl("texture image data freed");
		}
		ft_memdel((void**)(&textures));
		ft_putendl("textures pointer is is freed");
	}
}

void			deinit_env(t_env *env)
{
	deinit_map(env->map);
	ft_putendl("END MAP DEINIT");
	deinit_textures(env->textures, env->textures_count, env);
	ft_putendl("END TEXTURES DEINIT");
	if (env->img_ptr && env->mlx_ptr)
		mlx_destroy_image(env->mlx_ptr, env->img_ptr);
	ft_putendl("img_ptr freed");
	if (env->win_ptr && env->mlx_ptr)
		mlx_destroy_window(env->mlx_ptr, env->win_ptr);
	ft_putendl("win_ptr freed");
	ft_putendl("img_str freed");
	ft_memdel((void**)(&(env->mlx_ptr)));
	ft_putendl("mlx_ptr freed");
	ft_memdel((void**)(&env));
}
