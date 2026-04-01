/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_player.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaratr <mamaratr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 11:19:12 by mamaratr          #+#    #+#             */
/*   Updated: 2026/04/01 11:56:38 by mamaratr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub.h"

static void	minimap_player_pos(t_data *data, int *px, int *py)
{
	int	center_x;
	int	center_y;

	center_x = MINIMAP_X + (MINIMAP_TILES / 2) * 20;
	center_y = MINIMAP_Y + (MINIMAP_TILES / 2) * 20;
	*px = center_x + (int)((data->player.x - (int)data->player.x)
			* 20);
	*py = center_y + (int)((data->player.y - (int)data->player.y)
			* 20);
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
