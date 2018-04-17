/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmlynarc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 17:01:57 by jmlynarc          #+#    #+#             */
/*   Updated: 2018/04/17 17:15:01 by jmlynarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static t_texture	load_texture(char *path, t_env *env)
{
	t_texture		texture;

	texture.img_str = NULL;
	texture.img_ptr = NULL;
	texture.file_path = path;
	texture.img_ptr = mlx_xpm_file_to_image(env->mlx_ptr, path,
		&(texture.width), &(texture.height));
	texture.img_str = mlx_get_data_addr(texture.img_ptr, &(texture.bpp),
		&(texture.line_size), &(texture.endian));
	texture.line_size /= 4;
	return (texture);
}

static int			init_is_correct(t_texture *textures, int count)
{
	int			counter;
	t_texture	texture;

	counter = -1;
	while (++counter < count)
	{
		texture = textures[counter];
		if (texture.img_ptr == NULL || texture.img_str == NULL)
			return (0);
	}
	return (1);
}

void				init_textures(t_env *env)
{
	t_texture		*textures;
	int				counter;
	static char		*files[TEXTURES_COUNT] = {
		"textures/bluestone.xpm",
		"textures/colorstone.xpm",
		"textures/greystone.xpm",
		"textures/redbrick.xpm"
	};

	if (!(textures = (t_texture*)malloc(sizeof(t_texture) * TEXTURES_COUNT)))
		exit_error(env);
	counter = -1;
	while (++counter < TEXTURES_COUNT)
		textures[counter] = load_texture(files[counter], env);
	env->textures = textures;
	env->textures_count = TEXTURES_COUNT;
	if (!(init_is_correct(textures, TEXTURES_COUNT)))
		exit_error(env);
}
