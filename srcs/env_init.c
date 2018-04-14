#include "wolf3d.h"

static void			setup_environnement(t_env *env)
{
	env->mlx_ptr = mlx_init();
	env->win_ptr = mlx_new_window(env->mlx_ptr, WIN_WIDTH, WIN_HEIGHT,
		"Wolf 3D");
	env->win_width = WIN_WIDTH;
	env->win_height = WIN_HEIGHT;
}

static void			setup_camera(t_env *env)
{
	t_camera	camera;

	camera.pos_x = floor(3.5 * (double)TEXTURE_RES);
	camera.pos_y = floor(3.5 * (double)TEXTURE_RES);
	camera.angle = 3 * M_PI / 4;
	camera.height = TEXTURE_RES / 2;
	env->camera = camera;
}

t_env				*init_environnement(void)
{
	t_env		*env;

	if (!(env = (t_env*)malloc(sizeof(t_env))))
		return (NULL);
	env->mlx_ptr = NULL;
	env->win_ptr = NULL;
	env->img_ptr = NULL;
	env->img_str = NULL;
	setup_environnement(env);
	setup_camera(env);
	return (env);
}

