/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bigmap.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaratr <mamaratr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 11:20:15 by mamaratr          #+#    #+#             */
/*   Updated: 2026/02/26 12:15:37 by mamaratr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub.h"

static void	bigmap_draw_overlay(t_data *data)
{
	int				x;
	int				y;
	unsigned int	*px;

	y = 0;
	while (y < SCREEN_HEIGHT)
	{
		x = 0;
		while (x < SCREEN_WIDTH)
		{
			px = (unsigned int *)(data->img.addr
					+ (y * data->img.line_length + x * (data->img.bpp / 8)));
			*px = (*px >> 1 & 0x7F7F7F);
			x++;
		}
		y++;
	}
}

static void	bigmap_draw_loop(t_data *data, t_bigmap *bm)
{
	int					x;
	int					y;
	t_minimap_square	sq;

	y = -1;
	while (++y < bm->map_h)
	{
		x = 0;
		while (x < bm->map_w && data->map->map[y]
			&& x < (int)ft_strlen(data->map->map[y]))
		{
			if (data->map->map[y][x] == '1')
				bm->color = 0xDDDDDD;
			else if (data->map->map[y][x] == 'D')
				bm->color = 0xFF8800;
			else
				bm->color = 0x222222;
			sq.start_x = bm->off_x + x * bm->tile;
			sq.start_y = bm->off_y + y * bm->tile;
			sq.tile_size = bm->tile - 1;
			sq.color = bm->color;
			draw_square(data, sq);
			x++;
		}
	}
}

void	draw_bigmap(t_data *data)
{
	t_bigmap			bm;
	t_minimap_square	sq;

	bm.map_w = data->map->m_width;
	bm.map_h = data->map->m_height;
	bm.tile = (SCREEN_HEIGHT * 70 / 100) / bm.map_h;
	if (bm.tile < 4)
		bm.tile = 4;
	bm.total_w = bm.map_w * bm.tile;
	bm.total_h = bm.map_h * bm.tile;
	bm.off_x = (SCREEN_WIDTH - bm.total_w) / 2;
	bm.off_y = (SCREEN_HEIGHT - bm.total_h) / 2;
	bigmap_draw_overlay(data);
	bigmap_draw_loop(data, &bm);
	bm.px = bm.off_x + (int)(data->player.x * bm.tile) - 4;
	bm.py = bm.off_y + (int)(data->player.y * bm.tile) - 4;
	sq.start_x = bm.px;
	sq.start_y = bm.py;
	sq.tile_size = 8;
	sq.color = 0xFF2222;
	draw_square(data, sq);
}
