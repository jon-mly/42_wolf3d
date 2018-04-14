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
