/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarpio-cyepes <rcarpio-cyepes@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 15:47:00 by rcarpio-mam       #+#    #+#             */
/*   Updated: 2026/02/20 13:32:02 by rcarpio-cye      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	init_textures(char **file, t_data *data)
{
	int	i;

	i = 0;
	while (i < TEX_COUNT)
	{
		data->textures.paths[i] = NULL;
		i++;
	}
	parse_textures(file, data);
	data->textures.paths[TEX_DOOR] = "img/door_close.xpm";
	load_textures(data);
}

void	parse_textures(char **file, t_data *data)
{
	int	id;

	while (*file)
	{
		id = get_texture_id(*file);
		if (id != -1)
			data->textures.paths[id] = ft_strtrim(*file + 2, " \n");
		else
			break;
		file++;
	}
}

void	load_textures(t_data *data)
{
	int	i;

	i = 0;
	while (i < TEX_COUNT)
	{
		data->textures.images[i].img = mlx_xpm_file_to_image(data->mlx,
			data->textures.paths[i], &data->textures.images[i].width, &data->textures.images[i].height);
		data->textures.images[i].addr = mlx_get_data_addr(data->textures.images[i].img,
			&data->textures.images[i].bpp, &data->textures.images[i].line_length, &data->textures.images[i].endian);
		i++;
	}
}
