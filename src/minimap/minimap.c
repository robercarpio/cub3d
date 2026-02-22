/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaratr <mamaratr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 17:27:53 by mamaratr          #+#    #+#             */
/*   Updated: 2026/02/22 10:32:29 by mamaratr         ###   ########.fr       */
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

void	draw_square(t_data *data, int start_x, int start_y, int size, int color)
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

static void	check_if_wall(t_data *data, int map_x, int map_y, int *color)
{
	if (map_y >= 0 && map_y < data->map->m_height
		&& map_x >= 0 && data->map->map[map_y]
		&& map_x < (int)ft_strlen(data->map->map[map_y]))
	{
		if (data->map->map[map_y][map_x] == '1')
			*color = 0xFFFFFF;
	}
}

void	draw_minimap(t_data *data)
{
	int	mini_x;
	int	mini_y;
	int	map_x;
	int	map_y;
	int	color;

	mini_y = 0;
	while (mini_y < MINIMAP_TILES)
	{
		mini_x = 0;
		while (mini_x < MINIMAP_TILES)
		{
			color = 0x000000;
			map_x = (int)(data->player.x) - (MINIMAP_TILES / 2) + mini_x;
			map_y = (int)(data->player.y) - (MINIMAP_TILES / 2) + mini_y;
			check_if_wall(data, map_x, map_y, &color);
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

int	minimap_player_pos_x(t_data *data)
{
	int		center_tile_x;
	float	offset_x;
	int		player_x;

	center_tile_x = MINIMAP_X + (MINIMAP_TILES / 2) * MINIMAP_TILE_SIZE;
	offset_x = (data->player.x - (int)data->player.x) * MINIMAP_TILE_SIZE;
	player_x = center_tile_x + (int)offset_x;
	return (player_x);
}

int	minimap_player_pos_y(t_data *data)
{
	int		center_tile_y;
	float	offset_y;
	int		player_y;

	center_tile_y = MINIMAP_Y + (MINIMAP_TILES / 2) * MINIMAP_TILE_SIZE;
	offset_y = (data->player.y - (int)data->player.y) * MINIMAP_TILE_SIZE;
	player_y = center_tile_y + (int)offset_y;
	return (player_y);
}

void	draw_minimap_player(t_data *data)
{
	int	player_x;
	int	player_y;
	int	r;
	int	x;
	int	y;

	player_x = minimap_player_pos_x(data);
	player_y = minimap_player_pos_y(data);
	r = 5;
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
