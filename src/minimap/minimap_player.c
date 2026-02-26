/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_player.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaratr <mamaratr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 11:19:12 by mamaratr          #+#    #+#             */
/*   Updated: 2026/02/26 11:57:10 by mamaratr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub.h"

static void	minimap_player_pos(t_data *data, int *px, int *py)
{
	int	center_x;
	int	center_y;

	center_x = MINIMAP_X + (MINIMAP_TILES / 2) * MINIMAP_TILE_SIZE;
	center_y = MINIMAP_Y + (MINIMAP_TILES / 2) * MINIMAP_TILE_SIZE;
	*px = center_x + (int)((data->player.x - (int)data->player.x)
			* MINIMAP_TILE_SIZE);
	*py = center_y + (int)((data->player.y - (int)data->player.y)
			* MINIMAP_TILE_SIZE);
}

static void	set_triangle_points(t_data *data,
				t_minimap_player *p)
{
	p->perp_x = -data->player.dir_y;
	p->perp_y = data->player.dir_x;
	p->px[0] = p->player_x + data->player.dir_x * p->size;
	p->py[0] = p->player_y + data->player.dir_y * p->size;
	p->px[1] = p->player_x + p->perp_x * p->size / 2;
	p->py[1] = p->player_y + p->perp_y * p->size / 2;
	p->px[2] = p->player_x - p->perp_x * p->size / 2;
	p->py[2] = p->player_y - p->perp_y * p->size / 2;
}

static void	set_triangle_bounds(t_minimap_player *p)
{
	int	i;

	p->min_x = p->px[0];
	p->max_x = p->px[0];
	p->min_y = p->py[0];
	p->max_y = p->py[0];
	i = 1;
	while (i < 3)
	{
		if (p->px[i] < p->min_x)
			p->min_x = p->px[i];
		if (p->px[i] > p->max_x)
			p->max_x = p->px[i];
		if (p->py[i] < p->min_y)
			p->min_y = p->py[i];
		if (p->py[i] > p->max_y)
			p->max_y = p->py[i];
		i++;
	}
}

static void	fill_triangle(t_data *data, t_minimap_player *p)
{
	int	x;
	int	y;
	int	d1;
	int	d2;
	int	d3;

	y = p->min_y;
	while (y <= p->max_y)
	{
		x = p->min_x;
		while (x <= p->max_x)
		{
			d1 = (x - p->px[1]) * (p->py[0] - p->py[1])
				- (y - p->py[1]) * (p->px[0] - p->px[1]);
			d2 = (x - p->px[2]) * (p->py[1] - p->py[2])
				- (y - p->py[2]) * (p->px[1] - p->px[2]);
			d3 = (x - p->px[0]) * (p->py[2] - p->py[0])
				- (y - p->py[0]) * (p->px[2] - p->px[0]);
			if ((d1 >= 0 && d2 >= 0 && d3 >= 0)
				|| (d1 <= 0 && d2 <= 0 && d3 <= 0))
				my_mlx_pixel_put(&data->img, x, y, 0xFF0000);
			x++;
		}
		y++;
	}
}

void	draw_minimap_player(t_data *data)
{
	t_minimap_player	p;

	minimap_player_pos(data, &p.player_x, &p.player_y);
	p.size = 12;
	set_triangle_points(data, &p);
	set_triangle_bounds(&p);
	fill_triangle(data, &p);
}
