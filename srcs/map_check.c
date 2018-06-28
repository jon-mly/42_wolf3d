/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmlynarc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/28 14:42:58 by jmlynarc          #+#    #+#             */
/*   Updated: 2018/06/28 14:51:18 by jmlynarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

t_map		check_map(int index, int pos_index, t_map map)
{
	if (index == 0)
		map.width = pos_index;
	else if (pos_index != map.width)
		exit_wrong_map();
	return (map);
}
