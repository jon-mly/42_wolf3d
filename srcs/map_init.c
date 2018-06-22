/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmlynarc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/14 14:30:43 by jmlynarc          #+#    #+#             */
/*   Updated: 2018/06/22 16:17:06 by jmlynarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void		append_node(t_line **nodes, t_line *new_node)
{
	t_line		*current;

	current = *nodes;
	if (current == NULL)
		*nodes = new_node;
	else
	{
		while (current->next)
			current = current->next;
		current->next = new_node;
	}
}

static t_line	**get_lines(int fd)
{
	t_line		**nodes;
	t_line		*node;
	char		**tmp;
	char		**coordinates;

	if (!(nodes = (t_line**)malloc(sizeof(t_line*))))
		return (NULL);
	*nodes = NULL;
	if (!(tmp = (char**)malloc(sizeof(char*))))
		return (NULL);
	while ((get_next_line(fd, tmp)) > 0)
	{
		if (!(coordinates = ft_strsplit(*tmp, ' ')) || !(coordinates_are_convertible(coordinates)))
			return (NULL);
		// TODO: should check if coordinates are integer convertible
		if (!(node = (t_line*)malloc(sizeof(t_line))))
			return (NULL);
		node->line = coordinates;
		node->next = NULL;
		append_node(nodes, node);
		ft_strdel(tmp);
	}
	ft_strdel(tmp);
	ft_memdel((void**)&tmp);
	return ((nodes && *nodes) ? nodes : NULL);
}

static int		*get_array(char **line)
{
	size_t		len;
	int			*array;

	len = 0;
	while (line[len])
		len++;
	if (!(array = (int*)malloc(sizeof(int) * len)))
		return (NULL);
	return (array);
}

static t_map	set_up_map(t_map map, t_line **nodes, int height)
{
	t_line		*node;
	int			line_index;
	int			pos_index;

	node = *nodes;
	line_index = -1;
	while (node)
	{
		line_index++;
		pos_index = -1;
		if (!(map.map[line_index] = get_array(node->line)))
			return (map);
		while (node->line[++pos_index])
		{
			map.map[line_index][pos_index] = ft_atoi(node->line[pos_index]);
			ft_strdel(&node->line[pos_index]);
		}
		ft_memdel((void**)&node->line);
		*nodes = node;
		node = node->next;
		ft_memdel((void**)nodes);
	}
	map.width = pos_index;
	map.height = height;
	return (map);
}

t_map			*read_map_from(char *path)
{
	int			fd;
	t_line		**nodes;
	t_line		*node;
	int			height;
	t_map		*map;

	if ((fd = open(path, O_RDONLY)) < 3)
		return (NULL);
	if (!(map = (t_map*)malloc(sizeof(t_map))))
		return (NULL);
	ft_putendl("First tests are ok");
	if (!(nodes = get_lines(fd)))
		return (NULL);
	ft_putendl("Nodes are returned");
	close(fd);
	node = *nodes;
	height = 0;
	while (node)
	{
		node = node->next;
		height++;
	}
	if (!(map->map = (int**)malloc(sizeof(int*) * height)))
		return (NULL);
	*map = set_up_map(*map, nodes, height);
	ft_memdel((void**)&nodes);
	return (map);
}
