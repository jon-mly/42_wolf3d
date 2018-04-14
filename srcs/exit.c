#include "wolf3d.h"

void		exit_usage(void)
{
	ft_putendl("wolf3d [map file path]");
	exit(0);
}

void		exit_error(t_env *env)
{
	ft_putendl("An error has occured");
	// TODO: deinit env
	exit(0);
}

void		exit_normally(t_env *env)
{
	// TODO: deinit env
	exit(0);
}
