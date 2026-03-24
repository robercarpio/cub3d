/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_player.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaratr <mamaratr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 11:19:12 by mamaratr          #+#    #+#             */
/*   Updated: 2026/03/24 12:45:34 by mamaratr         ###   ########.fr       */
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

void	draw_minimap_player(t_data *data)
{
	int	px;
	int	py;
	int	x;
	int	y;

	minimap_player_pos(data, &px, &py);
	y = -3;
	while (y <= 3)
	{
		x = -3;
		while (x <= 3)
		{
			my_mlx_pixel_put(&data->img, px + x, py + y, 0xFF0000);
			x++;
		}
		y++;
	}
}
