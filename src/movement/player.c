/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaratr <mamaratr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 11:23:35 by mamaratr          #+#    #+#             */
/*   Updated: 2026/02/23 11:16:10 by mamaratr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	init_player(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (data->map->map[y])
	{
		x = 0;
		while (data->map->map[y][x])
		{
			if (data->map->map[y][x] == 'P')
			{
				data->player.x = x + 0.5;
				data->player.y = y + 0.5;
				data->player.dir_x = 0.0;
				data->player.dir_y = -1.0;
				data->player.plane_x = 0.66;
				data->player.plane_y = 0.0;
				data->map->map[y][x] = '0';
				return ;
			}
			x++;
		}
		y++;
	}
}

void	try_open_door(t_data *data)
{
	int	px;
	int	py;
	int	dx;
	int	dy;

	px = (int)data->player.x;
	py = (int)data->player.y;
	dy = -1;
	while (dy <= 1)
	{
		dx = -1;
		while (dx <= 1)
		{
			if (dx == 0 && dy == 0)
			{
				dx++;
				continue ;
			}
			if (py + dy >= 0 && py + dy < data->map->m_height
				&& data->map->map[py + dy]
				&& px + dx >= 0
				&& px + dx < (int)ft_strlen(data->map->map[py + dy])
				&& data->map->map[py + dy][px + dx] == 'D')
			{
				data->map->map[py + dy][px + dx] = '0';
				return ;
			}
			dx++;
		}
		dy++;
	}
}
