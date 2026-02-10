/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaratr <mamaratr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 15:47:00 by rcarpio-mam       #+#    #+#             */
/*   Updated: 2026/02/10 13:53:13 by mamaratr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	init_textures(t_texture *tex)
{
	int	i;

	i = 0;
	while (i < TEX_COUNT)
	{
		tex->paths[i] = NULL;
		i++;
	}
}

void	parse_textures(char **file, t_texture *tex)
{
	int	id;

	while (*file)
	{
		id = get_texture_id(*file);
		if (id != -1)
		{
			tex->paths[id] = ft_strtrim(*file + 2, " \n");
		}
		else
			break;
		file++;
	}
}

void	load_textures(t_data *data, t_texture *tex)
{
	int	i;

	i = 0;
	while (i < TEX_COUNT)
	{
		tex->images[i].img = mlx_xpm_file_to_image(data->mlx,
			tex->paths[i], &tex->images[i].width, &tex->images[i].height);
		tex->images[i].addr = mlx_get_data_addr(tex->images[i].img,
			&tex->images[i].bpp, &tex->images[i].line_length, &tex->images[i].endian);
		i++;
	}
}
