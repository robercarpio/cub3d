/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   background.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaratr <mamaratr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 11:44:31 by mamaratr          #+#    #+#             */
/*   Updated: 2026/02/13 13:38:54 by mamaratr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	draw_floor_ceiling(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < SCREEN_HEIGHT / 2)
	{
		x = 0;
		while (x < SCREEN_WIDTH)
		{
			my_mlx_pixel_put(&data->img, x, y, data->map->ceiling_color);
			x++;
		}
		y++;
	}
	y = SCREEN_HEIGHT / 2;
	while (y < SCREEN_HEIGHT)
	{
		x = 0;
		while (x < SCREEN_WIDTH)
		{
			my_mlx_pixel_put(&data->img, x, y, data->map->floor_color);
			x++;
		}
		y++;
	}
}