#include "wolf3d.h"

void		draw_ceiling(int x, int y, t_env *env)
{
	t_color		color;

	color.r = 100;
	color.g = 200;
	color.b = 255;
	color.a = 1;
	fill_pixel(env, x, y, color);
}

void		draw_floor(int x, int y, t_env *env)
{
t_color		color;

	color.r = 50;
	color.g = 100;
	color.b = 200;
	color.a = 1;
	fill_pixel(env, x, y, color);
}

void		draw_wall(int x, int y, t_env *env, t_cardinal cardinal)
{
	t_color		color;
	int			color_value;

	if (cardinal == NORTH || cardinal == SOUTH)
		color_value = 100;
	else if (cardinal == EAST)
		color_value = 130;
	else
		color_value = 70;
	color.r = color_value;
	color.g = color_value;
	color.b = color_value;
	color.a = 1;
	fill_pixel(env, x, y, color);
}

void		draw_column(int index, t_env *env, int wall_height,
	t_cardinal cardinal)
{
	int		line;

	line = -1;
	while (++line < WIN_HEIGHT)
	{
		if (line < -wall_height / 2 + MID_HEIGHT)
			draw_ceiling(index, line, env);
		else if (line > wall_height / 2 + MID_HEIGHT)
			draw_floor(index, line, env);
		else
			draw_wall(index, line, env, cardinal);
	}
}
