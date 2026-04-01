/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaratr <mamaratr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 17:27:53 by mamaratr          #+#    #+#             */
/*   Updated: 2026/04/01 11:56:23 by mamaratr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub.h"

void	draw_square(t_data *data, t_minimap_square minimap)
{
	int	x;
	int	y;

	y = 0;
	while (y < minimap.tile_size)
	{
		x = 0;
		while (x < minimap.tile_size)
		{
			my_mlx_pixel_put(&data->img, minimap.start_x + x, minimap.start_y
				+ y, minimap.color);
			x++;
		}
		y++;
	}
}

void	draw_minimap_border(t_data *data)
{
	int	layer;
	int	border_width;
	int	i;

	layer = 0;
	border_width = 4;
	while (layer < border_width)
	{
		i = 0;
		while (i < MINIMAP_SIZE + 2 * layer)
		{
			my_mlx_pixel_put(&data->img, MINIMAP_X - layer + i,
				MINIMAP_Y - layer, 0xAAAAAA);
			my_mlx_pixel_put(&data->img, MINIMAP_X - layer + i,
				MINIMAP_Y + MINIMAP_SIZE + layer, 0xAAAAAA);
			my_mlx_pixel_put(&data->img, MINIMAP_X - layer,
				MINIMAP_Y - layer + i, 0xAAAAAA);
			my_mlx_pixel_put(&data->img, MINIMAP_X + MINIMAP_SIZE + layer,
				MINIMAP_Y - layer + i, 0xAAAAAA);
			i++;
		}
		layer++;
	}
}

void	draw_minimap(t_data *data)
{
	int					mini_x;
	int					mini_y;
	int					map_x;
	int					map_y;
	t_minimap_square	sq;

	mini_y = 0;
	while (mini_y < MINIMAP_TILES)
	{
		mini_x = 0;
		while (mini_x < MINIMAP_TILES)
		{
			sq.color = 0x000000;
			map_x = (int)data->player.x - (MINIMAP_TILES / 2) + mini_x;
			map_y = (int)data->player.y - (MINIMAP_TILES / 2) + mini_y;
			check_if_wall(data, map_x, map_y, &sq.color);
			sq.start_x = MINIMAP_X + mini_x * 20;
			sq.start_y = MINIMAP_Y + mini_y * 20;
			sq.tile_size = 20;
			draw_square(data, sq);
			mini_x++;
		}
		mini_y++;
	}
}

void	draw_ray(t_data *data)
{
	int	player_x;
	int	player_y;
	int	r;
	int	x;
	int	y;

	player_x = data->dda.map_x * TILE_SIZE;
	player_y = data->dda.map_y * TILE_SIZE;
	r = 5;
	y = -r;
	while (y <= r)
	{
		x = -r;
		while (x <= r)
		{
			my_mlx_pixel_put(&data->img, player_x + x, player_y + y, 0xFFFF00);
			x++;
		}
		y++;
	}
}
