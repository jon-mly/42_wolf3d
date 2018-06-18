/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmlynarc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/14 14:31:14 by jmlynarc          #+#    #+#             */
/*   Updated: 2018/06/18 13:27:10 by jmlynarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

// !!!!
# include <stdio.h>

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
# include <time.h>

/*
** ======= macros
*/

# define WIN_WIDTH 1200
# define WIN_HEIGHT 800
# define MID_WIDTH 600
# define MID_HEIGHT 400

# define TEXTURE_RES 64
# define TEXTURES_COUNT 4

# define KEY_ESC 53
# define KEY_ARROW_UP 126
# define KEY_ARROW_DOWN 125
# define KEY_ARROW_LEFT 124
# define KEY_ARROW_RIGHT 123

# define WALL_HEIGHT 64
# define SCREEN_DISTANCE 250
# define CAMERA_HEIGHT 32
# define FOV 0.66

# define ROTATION_ANGLE M_PI / 12
# define ROTATION_PER_SEC M_PI
# define SPEED_PER_SEC 3.5
# define WALL_HIT_MARGIN 0.3

# define KEY_PRESS 2
# define KEY_PRESS_MASK (1L<<0)
# define KEY_RELEASE 3
# define KEY_RELEASE_MASK (1L<<1)
# define WIN_CROSS 17
# define NO_MASK 0

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

typedef enum	e_ray_side
{
	HORIZONTAL,
	VERTICAL
}				t_ray_side;

typedef enum	e_surface
{
	EMPTY,
	WALL
}				t_surface;

typedef enum	e_cam_rotation
{
	LEFT,
	RIGHT
}				t_cam_rotation;

typedef enum	e_cam_move
{
	BACKWARD,
	FORWARD
}				t_cam_move;

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
	double		x_direction;
	double		y_direction;
	double		wall_distance;
	int			wall_pixel_height;
	t_surface	surface;
	t_ray_side	side;
	t_cardinal	cardinal;
}				t_ray;

typedef struct	s_camera
{
	t_vector		position;
	t_vector		direction;
	t_vector		projection;
	double			angle;
	int				height;
	int				move;
	t_cam_move		move_side;
	int				rotate;
	t_cam_rotation	rotation_side;
}				t_camera;

typedef struct	s_map
{
	int			**map;
	int			height;
	int			width;
}				t_map;

typedef struct	s_texture
{
	char		*file_path;
	int			height;
	int			width;
	void		*img_ptr;
	char		*img_str;
	int			bpp;
	int			line_size;
	int			endian;
}				t_texture;

typedef struct	s_timer
{
	clock_t		previous_time;
	clock_t		current_time;
	clock_t		next_frame;
	double		frame_time;
}				t_timer;

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
	t_map			*map;
	t_camera		camera;
	int				textures_count;
	t_texture		*textures;
	t_timer			timer;
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
void			fill_pixel_value(t_env *env, int x, int y, int color_value);
void			cast_ray(int index, t_env *env);
void			redraw_scene(t_env *env);
t_cardinal		cardinal_for_wall(double horizontal_distance,
	double vertical_distance, double angle);
void			draw_ceiling(int x, int y, t_env *env);
void			draw_floor(int x, int y, t_env *env);
void			draw_wall(int x, int y, t_env *env, t_cardinal cardinal);
void			draw_column(int index, t_env *env, t_ray ray);
void			deinit_env(t_env *env);
void			init_textures(t_env *env);
void			apply_texture_on_line(int line, t_env *env, t_ray ray);
int				move_camera_if_needed(t_env *env);
int				no_event_loop(void *param);
int				key_press(int key, void *param);
int				key_release(int key, void *param);
int				event_hook(void *param);

#endif
