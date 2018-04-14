/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   angle_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmlynarc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/14 14:30:03 by jmlynarc          #+#    #+#             */
/*   Updated: 2018/04/14 14:30:05 by jmlynarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

/*
** horizontal_distance : shorter distance between the camera and an horizontal
** wall.
** vertical_distance : shorter distance between the camera and a vertical
** wall.
** angle : the angle of the casted ray
*/

t_cardinal		cardinal_for_wall(double horizontal_distance,
	double vertical_distance, double angle)
{
	if (fmin(horizontal_distance, vertical_distance) == vertical_distance)
		return (cos(angle) >= 0) ? EAST : WEST;
	else
		return (sin(angle) >= 0) ? NORTH : SOUTH;
}
