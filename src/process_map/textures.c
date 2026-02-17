/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarpio-mamaratr <rcarpio-mamaratr@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 15:47:00 by rcarpio-mam       #+#    #+#             */
/*   Updated: 2026/02/16 11:43:38 by rcarpio-mam      ###   ########.fr       */
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
	// printf("in call init textures\n");
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
	// printf("in call load textures\n");
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
