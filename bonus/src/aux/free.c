/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarpio-cyepes <rcarpio-cyepes@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 10:52:15 by rcarpio-mam       #+#    #+#             */
/*   Updated: 2026/02/24 14:44:11 by rcarpio-cye      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	free_arr(char **arr)
{
	int	i;

	i = -1;
	while (arr[++i])
		free(arr[i]);
	free(arr);
}

void	free_data(t_data **data)
{
	if (!data || !*data)
		return ;
	if ((*data)->keys)
		free((*data)->keys);
	if ((*data)->map)
	{
		if ((*data)->map->map)
			free_arr((*data)->map->map);
		free((*data)->map);
	}
	if ((*data)->mlx)
	{
		if ((*data)->img.img)
			mlx_destroy_image((*data)->mlx, (*data)->img.img);
		if ((*data)->msg_e.img)
			mlx_destroy_image((*data)->mlx, (*data)->msg_e.img);
		// Los paths y las imágenes dentro de t_texture son estáticos o
		// deben liberarse si fueron strdup.
		// En textures.c, parse_textures usa ft_strtrim que reserva memoria.
		int i = 0;
		while (i < TEX_COUNT)
		{
			if ((*data)->textures.paths[i])
				free((*data)->textures.paths[i]);
			if ((*data)->textures.images[i].img)
				mlx_destroy_image((*data)->mlx, (*data)->textures.images[i].img);
			i++;
		}
		// mlx y win se gestionan a través de mlx_destroy_window si fuera necesario,
		// pero aquí cerramos el proceso.
	}
	free(*data);
	*data = NULL;
}
