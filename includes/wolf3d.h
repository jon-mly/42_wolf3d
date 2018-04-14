/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmlynarc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/14 14:31:14 by jmlynarc          #+#    #+#             */
/*   Updated: 2018/04/14 16:09:28 by jmlynarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

/*
** ======= includes
*/

# include "mlx.h"
# include "../libft/libft.h"
# include <math.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <math.h>

/*
** ======= macros
*/

# define WIN_WIDTH 1200
# define WIN_HEIGHT 800
# define MID_WIDTH 600
# define MID_HEIGHT 400

# define TEXTURE_RES 64
//# define EMPTY 0
//# define WALL 1

# define KEY_ESC 53
# define KEY_ARROW_UP 126
# define KEY_ARROW_DOWN 125
# define KEY_ARROW_LEFT 124
# define KEY_ARROW_RIGHT 123

# define WALL_HEIGHT 64
# define SCREEN_DISTANCE 250 //floor((double)600 / tan(M_PI / 6))
# define CAMERA_HEIGHT 32
# define FOV 0.66

# define ROTATION_ANGLE M_PI / 12

/*
** ====== enumerations
*/

typedef enum	e_cardinal
{
	NORTH,
	EAST,
	WEST,
	SOUTH
}				t_cardinal;

typedef enum	e_surface
{
	EMPTY,
	WALL
}				t_surface;

/*
** ====== structures
*/

typedef struct	s_color
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
	unsigned char	a;
}				t_color;

typedef struct	s_line
{
	char			**line;
	struct s_line	*next;
}				t_line;

typedef struct	s_point
{
	int			x;
	int			y;
}				t_point;

typedef struct	s_vector
{
	double		x;
	double		y;
}				t_vector;

typedef struct	s_ray
{
	t_vector	direction;
	t_point		map_position;
	t_vector	side_shift;
	double		delta_x;
	double		delta_y;
	int			x_direction;
	int			y_direction;
	double		wall_distance;
	t_surface	surface;
	t_cardinal	side;
}				t_ray;

typedef struct	s_camera
{
	t_vector	position;
	t_vector	direction;
	t_vector	projection;
	double		angle;
	int			height;
}				t_camera;

typedef struct	s_map
{
	int			**map;
	int			height;
	int			width;
}				t_map;

typedef struct	s_env
{
	void			*mlx_ptr;
	void			*win_ptr;
	int				win_height;
	int				win_width;
	void			*img_ptr;
	unsigned char	*img_str;
	int				img_height;
	int				img_width;
	int				line_size;
	t_map			map;
	t_camera		camera;
}				t_env;

/*
** ====== prototypes
*/

void			exit_usage(void);
void			exit_error(t_env *env);
void			exit_normally(t_env *env);
t_map			*read_map_from(char *path);
int				is_integer_convertible(char *str);
t_env			*init_environnement(void);
double			min_horizontal_distance(t_env *env, double angle);
double			min_vertical_distance(t_env *env, double angle);
void			fill_pixel(t_env *env, int x, int y, t_color color);
void			cast_ray(int index, t_env *env);
void			redraw_scene(t_env *env);
int				deal_with_key(int key, void *param);
t_cardinal		cardinal_for_wall(double horizontal_distance,
	double vertical_distance, double angle);
#endif
