/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaratr <mamaratr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 17:27:53 by mamaratr          #+#    #+#             */
/*   Updated: 2026/02/13 12:53:46 by mamaratr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, unsigned int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= SCREEN_WIDTH || y >= SCREEN_HEIGHT)
		return ;
	dst = img->addr + (y * img->line_length + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

void	draw_square(t_data *data, int start_x, int start_y, int size,  int color)
{
	int	x;
	int	y;

	y = 0;
	while (y < size)
	{
		x = 0;
		while (x < size)
		{
			my_mlx_pixel_put(&data->img, start_x + x, start_y + y, color);
			x++;
		}
		y++;
	}
}

void draw_minimap_player(t_data *data)
{
	int center_x = MINIMAP_X + MINIMAP_SIZE / 2;
	int center_y = MINIMAP_Y + MINIMAP_SIZE / 2;

	int r = 4;
	int x;
	int y;

	y = -r;
	while (y <= r)
	{
		x = -r;
		while (x <= r)
		{
			my_mlx_pixel_put(&data->img, center_x + x, center_y + y, 0xFF0000);
			x++;
		}
		y++;
	}
}

void draw_minimap_border(t_data *data)
{
	int i = 0;
	while (i < MINIMAP_SIZE)
	{
		my_mlx_pixel_put(&data->img, MINIMAP_X + i, MINIMAP_Y, 0xAAAAAA);
		my_mlx_pixel_put(&data->img, MINIMAP_X + i, MINIMAP_Y + MINIMAP_SIZE, 0xAAAAAA);
		my_mlx_pixel_put(&data->img, MINIMAP_X, MINIMAP_Y + i, 0xAAAAAA);
		my_mlx_pixel_put(&data->img, MINIMAP_X + MINIMAP_SIZE, MINIMAP_Y + i, 0xAAAAAA);
		i++;
	}
}


void draw_minimap(t_data *data)
{
	int mini_x;
	int mini_y;
	int map_x;
	int map_y;

	int player_tile_x = (int)(data->player.x);
	int player_tile_y = (int)(data->player.y);
	int half = MINIMAP_TILES / 2;

	mini_y = 0;
	while (mini_y < MINIMAP_TILES)
	{
		mini_x = 0;
		while (mini_x < MINIMAP_TILES)
		{
			map_x = player_tile_x - half + mini_x;
			map_y = player_tile_y - half + mini_y;

			if (map_y >= 0 && map_x >= 0 &&
				data->map->map[map_y] &&
				map_x < (int)ft_strlen(data->map->map[map_y]))
			{
				if (data->map->map[map_y][map_x] == '1')
					draw_square(data,
						MINIMAP_X + mini_x * MINIMAP_TILE_SIZE,
						MINIMAP_Y + mini_y * MINIMAP_TILE_SIZE,
						MINIMAP_TILE_SIZE,
						0xFFFFFF);
				else
					draw_square(data,
						MINIMAP_X + mini_x * MINIMAP_TILE_SIZE,
						MINIMAP_Y + mini_y * MINIMAP_TILE_SIZE,
						MINIMAP_TILE_SIZE,
						0x000000);
			}
			else
			{
				// Outside map → void
				draw_square(data,
					MINIMAP_X + mini_x * MINIMAP_TILE_SIZE,
					MINIMAP_Y + mini_y * MINIMAP_TILE_SIZE,
					MINIMAP_TILE_SIZE,
					0x000000);
			}
			mini_x++;
		}
		mini_y++;
	}
}


void	clear_image(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < SCREEN_HEIGHT)
	{
		x = 0;
		while (x < SCREEN_WIDTH)
		{
			my_mlx_pixel_put(&data->img, x, y, 0x000000);
			x++;
		}
		y++;
	}
}