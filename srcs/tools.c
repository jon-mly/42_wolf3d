#include "wolf3d.h"

int		is_integer_convertible(char *str)
{
	size_t		i;

	i = -1;
	while (str[++i])
	{
		if ((i == 0 && !(ft_isdigit(str[i])) && str[i] != '-' && str[i] != '+')
			|| (i > 0 && !(ft_isdigit(str[i]))))
			return (0);
	}
	return (1);
}
