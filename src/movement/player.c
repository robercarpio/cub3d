/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarpio-cyepes <rcarpio-cyepes@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 11:23:35 by mamaratr          #+#    #+#             */
/*   Updated: 2026/02/20 16:34:14 by rcarpio-cye      ###   ########.fr       */
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

static int is_walkable(t_data *data, double x, double y)
{
	int map_x = (int)x;
	int map_y = (int)y;

	if (map_y < 0 || map_y >= data->map->m_height)
		return (0);
	if (!data->map->map[map_y])
		return (0);
	if (map_x < 0 || map_x >= (int)ft_strlen(data->map->map[map_y]))
		return (0);
	if (data->map->map[map_y][map_x] == '1')
		return (0);
	if (data->map->map[map_y][map_x] == 'D')
		return (0);
	return (1);
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

static void move_player(t_data *data, double move_x, double move_y)
{
	double new_x = data->player.x + move_x;
	double new_y = data->player.y + move_y;
	double r = PLAYER_RADIUS;

	if (is_walkable(data, new_x - r, data->player.y - r) &&
		is_walkable(data, new_x + r, data->player.y - r) &&
		is_walkable(data, new_x - r, data->player.y + r) &&
		is_walkable(data, new_x + r, data->player.y + r))
	{
		data->player.x = new_x;
	}
	if (is_walkable(data, data->player.x - r, new_y - r) &&
		is_walkable(data, data->player.x + r, new_y - r) &&
		is_walkable(data, data->player.x - r, new_y + r) &&
		is_walkable(data, data->player.x + r, new_y + r))
	{
		data->player.y = new_y;
	}
}


void	move_forward(t_data *data, int dir)
{
	move_player(data,
		data->player.dir_x * MOVE_SPEED * dir,
		data->player.dir_y * MOVE_SPEED * dir);
}

void	move_strafe(t_data *data, int dir)
{
	double perp_x = -data->player.dir_y;
	double perp_y = data->player.dir_x;

	move_player(data,
		perp_x * MOVE_SPEED * dir,
		perp_y * MOVE_SPEED * dir);
}

void	rotate_player(t_data *data, double angle)
{
	double	old_dir_x;
	double	old_plane_x;
	double	cos_angle;
	double	sin_angle;

	cos_angle = cos(angle);
	sin_angle = sin(angle);
	
	old_dir_x = data->player.dir_x;
	old_plane_x = data->player.plane_x;
	
	data->player.dir_x = data->player.dir_x * cos_angle
		- data->player.dir_y * sin_angle;
	data->player.dir_y = old_dir_x * sin_angle
		+ data->player.dir_y * cos_angle;
	data->player.plane_x = data->player.plane_x * cos_angle
		- data->player.plane_y * sin_angle;
	data->player.plane_y = old_plane_x * sin_angle
		+ data->player.plane_y * cos_angle;	
	if (DEBUG_MODE)
	{
		printf("PLAYER DIR X :%f \n", data->player.dir_x);
		printf("PLAYER DIR Y :%f \n", data->player.dir_y);
		printf("----------------------------------------------------------------------------------------------------------------------\n");
	}
}
