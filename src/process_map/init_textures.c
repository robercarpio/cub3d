/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarpio-mamaratr <rcarpio-mamaratr@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 15:47:00 by rcarpio-mam       #+#    #+#             */
/*   Updated: 2026/01/19 16:50:22 by rcarpio-mam      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

t_texture init_textures(char **file)
{
    t_texture	texture;
    int			i;

	i = 0;
	while (file[i])
	{

		if (is_texture(file[i]) > 0)
		{
			if(is_texture(file[i]) == 1)
				texture.north = file[i];
			if(is_texture(file[i]) == 2)
				texture.south = file[i];
			if(is_texture(file[i]) == 3)
				texture.west = file[i];
			if(is_texture(file[i]) == 4)
				texture.east = file[i];
		}
		i++;
	}
	return (texture);
}