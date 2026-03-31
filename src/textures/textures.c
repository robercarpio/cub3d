/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaratr <mamaratr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 15:47:00 by rcarpio-mam       #+#    #+#             */
/*   Updated: 2026/03/31 12:11:19 by mamaratr         ###   ########.fr       */
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
	int		id;
	char	*route;

	while (*file)
	{
		if ((*file)[0] == '\n' || (*file)[0] == '\0' || (*file)[0] == 'F'
			|| (*file)[0] == 'C')
		{
			file++;
			continue ;
		}
		if ((*file)[0] == '1' || (*file)[0] == '0')
			break ;
		id = get_texture_id(*file);
		route = ft_strtrim(*file + 3, " \n");
		if (id != -1 && access(route, F_OK) != -1)
			data->textures.paths[id] = route;
		else
			free(route);
		file++;
	}
}

void	load_textures(t_data *data)
{
	int	i;

	i = 0;
	while (i < TEX_COUNT)
	{
		if (data->textures.paths[i] == NULL)
		{
			printf("Error: invalid texture path\n");
			exit(-1);
		}
		else
		{
			data->textures.images[i].img = mlx_xpm_file_to_image(data->mlx,
					data->textures.paths[i], &data->textures.images[i].width,
					&data->textures.images[i].height);
			data->textures.images[i].addr = mlx_get_data_addr(
					data->textures.images[i].img, &data->textures.images[i].bpp,
					&data->textures.images[i].line_length,
					&data->textures.images[i].endian);
		}
		i++;
	}
}
