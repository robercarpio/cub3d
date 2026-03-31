/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaratr <mamaratr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 13:28:41 by mamaratr          #+#    #+#             */
/*   Updated: 2026/03/31 13:29:46 by mamaratr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	ft_free_text(t_data *data)
{
	int	i;

	i = -1;
	while (++i < TEX_COUNT)
	{
		if (data->textures.paths[i] && i != TEX_DOOR)
			free(data->textures.paths[i]);
		if (data->textures.images[i].img)
			mlx_destroy_image(data->mlx, data->textures.images[i].img);
	}
}

void	ft_free(t_data *data)
{
	if (data->keys)
		free(data->keys);
	ft_free_text(data);
	if (data->msg_e.img)
		mlx_destroy_image(data->mlx, data->msg_e.img);
	if (data->img.img)
		mlx_destroy_image(data->mlx, data->img.img);
	if (data->bgnd.img)
		mlx_destroy_image(data->mlx, data->bgnd.img);
	if (data->map)
	{
		if (data->map->map)
			free_map(data->map->map);
		free(data->map);
	}
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	if (data->mlx)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
}
