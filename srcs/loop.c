#include "wolf3d.h"

int			no_event_loop(void *param)
{
	t_env		*env;

	env = (t_env*)param;
	redraw_scene(env);
	return (0);
}

int			key_press(int key, void *param)
{
	t_env	*env;

//	ft_putendl("Key press triggered");
	env = (t_env*)param;
	if (key == KEY_ARROW_UP || key == KEY_ARROW_DOWN)
	{
		env->camera.move = 1;
		env->camera.move_side = (key == KEY_ARROW_UP) ? FORWARD : BACKWARD;
	}
	else if (key == KEY_ARROW_LEFT || key == KEY_ARROW_RIGHT)
	{
		env->camera.rotate = 1;
		env->camera.rotation_side = (key == KEY_ARROW_LEFT) ? LEFT : RIGHT;
	}
	else if (key == KEY_ESC)
	{
		exit_normally(env);
		return (0);
	}
	return (0);
}

int			key_release(int key, void *param)
{
	t_env	*env;

//	ft_putendl("Key release triggered");
	env = (t_env*)param;
	if (key == KEY_ARROW_UP || key == KEY_ARROW_DOWN)
		env->camera.move = 0;
	else if (key == KEY_ARROW_LEFT || key == KEY_ARROW_RIGHT)
		env->camera.rotate = 0;
	return (0);
}
