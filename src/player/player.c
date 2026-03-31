/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaratr <mamaratr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 11:23:35 by mamaratr          #+#    #+#             */
/*   Updated: 2026/03/31 13:54:17 by mamaratr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	set_player_dir_ns(t_player *player, char dir)
{
	if (dir == 'N')
	{
		player->dir_x = 0.0;
		player->dir_y = -1.0;
		player->plane_x = 0.66;
		player->plane_y = 0.0;
	}
	else
	{
		player->dir_x = 0.0;
		player->dir_y = 1.0;
		player->plane_x = -0.66;
		player->plane_y = 0.0;
	}
}

void	set_player_dir_we(t_player *player, char dir)
{
	if (dir == 'W')
	{
		player->dir_x = -1.0;
		player->dir_y = 0.0;
		player->plane_x = 0.0;
		player->plane_y = -0.66;
	}
	else
	{
		player->dir_x = 1.0;
		player->dir_y = 0.0;
		player->plane_x = 0.0;
		player->plane_y = 0.66;
	}
}

void	set_player_dir(t_player *player, char dir)
{
	if (dir == 'N' || dir == 'S')
		set_player_dir_ns(player, dir);
	else
		set_player_dir_we(player, dir);
}

void	init_player(t_data *data)
{
	int		x;
	int		y;
	char	dir;

	y = 0;
	while (data->map->map[y])
	{
		x = 0;
		while (data->map->map[y][x])
		{
			dir = data->map->map[y][x];
			if (dir == 'N' || dir == 'S' || dir == 'W' || dir == 'E')
			{
				data->player.x = x + 0.5;
				data->player.y = y + 0.5;
				set_player_dir(&data->player, dir);
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
	int		px;
	int		py;
	int		dx;
	int		dy;
	char	*row;

	px = (int)data->player.x;
	py = (int)data->player.y;
	dy = -1;
	while (dy <= 1)
	{
		dx = -1;
		while (dx <= 1)
		{
			row = data->map->map[py + dy];
			if ((dx || dy) && row && is_door_at(data, px + dx, py + dy)
				&& is_facing_door(data))
				return (toggle_door(row, px + dx));
			dx++;
		}
		dy++;
	}
}
