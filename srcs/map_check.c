/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmlynarc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/28 14:42:58 by jmlynarc          #+#    #+#             */
/*   Updated: 2018/06/29 14:54:14 by jmlynarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

t_map		check_map(int index, int pos_index, t_map map)
{
	if (index == 0)
		map.width = pos_index;
	else if (pos_index != map.width)
		exit_error(NULL, "Map is not a rectangle");
	return (map);
}

int			position_is_in_bounds(t_point point, t_map map)
{
	if (point.x < 0 || point.x >= map.width || point.y < 0 ||
			point.y >= map.height)
		return (0);
	return (1);
}

int			map_surrounded_by_walls(t_map map)
{
	int			y;
	int			x;

	x = -1;
	while (++x < map.width)
	{
		if (map.map[0][x] != WALL || map.map[map.height - 1][x] != WALL)
			return (0);
	}
	y = 0;
	while (++y < map.height - 1)
	{
		if (map.map[y][0] != WALL || map.map[y][map.width - 1] != WALL)
			return (0);
	}
	return (1);
}
