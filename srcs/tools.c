/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmlynarc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/14 14:30:54 by jmlynarc          #+#    #+#             */
/*   Updated: 2018/06/22 16:12:48 by jmlynarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int		coordinates_are_convertible(char **coordinates)
{
	int			i;

	i = -1;
	while (coordinates[++i])
	{
		if (!(is_integer_convertible(coordinates[i])))
			return (0);
	}
	return (1);
}
