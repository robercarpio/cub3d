/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaratr <mamaratr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 17:27:53 by mamaratr          #+#    #+#             */
/*   Updated: 2026/02/23 12:36:08 by mamaratr         ###   ########.fr       */
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

static void	draw_minimap_triangle(t_data *data, int cx, int cy, int size)
{
	int	px[3];
	int	py[3];
	float	perp_x;
	float	perp_y;
	int	min_x;
	int	max_x;
	int	min_y;
	int	max_y;
	int	x;
	int	y;
	int	i;

	perp_x = -data->player.dir_y;
	perp_y = data->player.dir_x;

	px[0] = cx + data->player.dir_x * size;
	py[0] = cy + data->player.dir_y * size;

	px[1] = cx + perp_x * size / 2;
	py[1] = cy + perp_y * size / 2;

	px[2] = cx - perp_x * size / 2;
	py[2] = cy - perp_y * size / 2;

	min_x = px[0];
	max_x = px[0];
	min_y = py[0];
	max_y = py[0];

	i = 1;
	while (i < 3)
	{
		if (px[i] < min_x) min_x = px[i];
		if (px[i] > max_x) max_x = px[i];
		if (py[i] < min_y) min_y = py[i];
		if (py[i] > max_y) max_y = py[i];
		i++;
	}

	y = min_y;
	while (y <= max_y)
	{
		x = min_x;
		while (x <= max_x)
		{
			int d1 = (x - px[1]) * (py[0] - py[1])
				- (y - py[1]) * (px[0] - px[1]);

			int d2 = (x - px[2]) * (py[1] - py[2])
				- (y - py[2]) * (px[1] - px[2]);

			int d3 = (x - px[0]) * (py[2] - py[0])
				- (y - py[0]) * (px[2] - px[0]);

			if ((d1 >= 0 && d2 >= 0 && d3 >= 0) ||
				(d1 <= 0 && d2 <= 0 && d3 <= 0))
				my_mlx_pixel_put(&data->img, x, y, 0xFF0000);

			x++;
		}
		y++;
	}
}

void	draw_minimap_player(t_data *data)
{
	int	player_x;
	int	player_y;

	player_x = minimap_player_pos_x(data);
	player_y = minimap_player_pos_y(data);
	draw_minimap_triangle(data, player_x, player_y, 12);
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

static void	bigmap_draw_overlay(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < SCREEN_HEIGHT)
	{
		x = 0;
		while (x < SCREEN_WIDTH)
		{
			unsigned int *px = (unsigned int *)(data->img.addr
				+ (y * data->img.line_length + x * (data->img.bpp / 8)));
			*px = (*px >> 1 & 0x7F7F7F);
			x++;
		}
		y++;
	}
}

void	draw_bigmap(t_data *data)
{
	int		map_w;
	int		map_h;
	int		tile;
	int		total_w;
	int		total_h;
	int		off_x;
	int		off_y;
	int		mx;
	int		my;
	int		color;
	int		px;
	int		py;

	map_w = data->map->m_width;
	map_h = data->map->m_height;
	tile = (SCREEN_HEIGHT * 70 / 100) / map_h;
	if (tile < 4)
		tile = 4;
	total_w = map_w * tile;
	total_h = map_h * tile;
	off_x = (SCREEN_WIDTH - total_w) / 2;
	off_y = (SCREEN_HEIGHT - total_h) / 2;

	bigmap_draw_overlay(data);

	my = 0;
	while (my < map_h)
	{
		mx = 0;
		while (mx < map_w && data->map->map[my]
			&& mx < (int)ft_strlen(data->map->map[my]))
		{
			if (data->map->map[my][mx] == '1')
				color = 0xDDDDDD;
			else if (data->map->map[my][mx] == 'D')
				color = 0xFF8800;
			else
				color = 0x222222;
			draw_square(data,
				off_x + mx * tile,
				off_y + my * tile,
				tile - 1,
				color);
			mx++;
		}
		my++;
	}
	px = off_x + (int)(data->player.x * tile) - 4;
	py = off_y + (int)(data->player.y * tile) - 4;
	draw_square(data, px, py, 8, 0xFF2222);
}
