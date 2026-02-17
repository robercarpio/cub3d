/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaratr <mamaratr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 17:27:53 by mamaratr          #+#    #+#             */
/*   Updated: 2026/02/17 09:35:02 by mamaratr         ###   ########.fr       */
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

void	draw_minimap_border(t_data *data)
{
	int	layer;
	int	border_width;

	layer = 0;
	border_width = 4;
	while (layer < border_width)
	{
		int i = 0;
		while (i < MINIMAP_SIZE + 2 * layer)
		{
			my_mlx_pixel_put(&data->img, MINIMAP_X - layer + i, MINIMAP_Y - layer, 0xAAAAAA);
			my_mlx_pixel_put(&data->img, MINIMAP_X - layer + i, MINIMAP_Y + MINIMAP_SIZE + layer, 0xAAAAAA);
			my_mlx_pixel_put(&data->img, MINIMAP_X - layer, MINIMAP_Y - layer + i, 0xAAAAAA);
			my_mlx_pixel_put(&data->img, MINIMAP_X + MINIMAP_SIZE + layer, MINIMAP_Y - layer + i, 0xAAAAAA);
			i++;
		}
		layer++;
	}
}

void	draw_minimap(t_data *data)
{
	int mini_x, mini_y;
	int map_x, map_y;

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

			int color = 0x000000; // default: empty space

			if (map_y >= 0 && map_y < data->map->m_height && // check bounds
				map_x >= 0 &&
				data->map->map[map_y] &&
				map_x < (int)ft_strlen(data->map->map[map_y]))
			{
				if (data->map->map[map_y][map_x] == '1')
					color = 0xFFFFFF;
			}
			draw_square(data,
				MINIMAP_X + mini_x * MINIMAP_TILE_SIZE,
				MINIMAP_Y + mini_y * MINIMAP_TILE_SIZE,
				MINIMAP_TILE_SIZE,
				color);

			mini_x++;
		}
		mini_y++;
	}
}

void draw_minimap_player(t_data *data)
{
	int center_tile_x = MINIMAP_X + (MINIMAP_TILES / 2) * MINIMAP_TILE_SIZE;
	int center_tile_y = MINIMAP_Y + (MINIMAP_TILES / 2) * MINIMAP_TILE_SIZE;

	float offset_x = (data->player.x - (int)data->player.x) * MINIMAP_TILE_SIZE;
	float offset_y = (data->player.y - (int)data->player.y) * MINIMAP_TILE_SIZE;

	int player_x = center_tile_x + (int)offset_x;
	int player_y = center_tile_y + (int)offset_y;

	int r = 5;
	int y = -r;
	int x;

	while (y <= r)
	{
		x = -r;
		while (x <= r)
		{
			my_mlx_pixel_put(&data->img, player_x + x, player_y + y, 0xFF0000);
			x++;
		}
		y++;
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
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarpio-mamaratr <rcarpio-mamaratr@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 17:27:53 by mamaratr          #+#    #+#             */
/*   Updated: 2026/02/12 16:44:35 by rcarpio-mam      ###   ########.fr       */
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

void	draw_player(t_data *data)
{
	int	player_x;
	int	player_y;
	int	r;
	int	x;
	int	y;

	r = 5;
	player_x = data->player.x * TILE_SIZE;
	player_y = data->player.y * TILE_SIZE;
	y = -r;
	while (y <= r)
	{
		x = -r;
		while (x <= r)
		{
			my_mlx_pixel_put(&data->img, player_x + x, player_y + y, 0xFF0000);
			x++;
		}
		y++;
	}
}

void	draw_ray(t_data *data)
{
	int	player_x;
	int	player_y;
	int	r;
	int	x;
	int	y;

	r = 5;
	player_x = data->dda.mapX * TILE_SIZE;
	player_y = data->dda.mapY * TILE_SIZE;
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

void	draw_map(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while(data->map->map[y])
	{
		x = 0;
		while(data->map->map[y][x])
		{
			if (data->map->map[y][x] == '1')
				draw_square(data, x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, 0xFFFFFF);
			else if (data->map->map[y][x] == '0')
				draw_square(data, x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, 0x000000);
			x++;
		}
		y++;
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