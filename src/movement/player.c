/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarpio-mamaratr <rcarpio-mamaratr@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 11:23:35 by mamaratr          #+#    #+#             */
/*   Updated: 2026/02/27 13:36:01 by rcarpio-mam      ###   ########.fr       */
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
			if (data->map->map[y][x] == 'N' || data->map->map[y][x] == 'S' ||
				data->map->map[y][x] == 'W' || data->map->map[y][x] == 'E')
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

static int	is_door_at(t_data *data, int x, int y)
{
	if (y < 0 || y >= data->map->m_height)
		return (0);
	if (!data->map->map[y])
		return (0);
	if (x < 0 || x >= (int)ft_strlen(data->map->map[y]))
		return (0);
	if (data->map->map[y][x] != 'D' && data->map->map[y][x] != 'd')
		return (0);
	return (1);
}

static void	toggle_door(char *row, int x)
{
	if (row[x] == 'D')
		row[x] = 'd';
	else
		row[x] = 'D';
}

static int	is_facing_door(t_data *data)
{
	int	map_x;
	int	map_y;
	int	i;

	i = 1;
	while (i <= 2)
	{
		map_x = (int)(data->player.x + data->player.dir_x * i);
		map_y = (int)(data->player.y + data->player.dir_y * i);
		if (is_door_at(data, map_x, map_y))
			return (1);
		if (data->map->map[map_y][map_x] == '1')
			return (0);
		i++;
	}
	return (0);
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


void	check_door_proximity(t_data *data)
{
	int	px;
	int	py;
	int	dx;
	int	dy;

	data->can_open_door = 0;
	px = (int)data->player.x;
	py = (int)data->player.y;
	dy = -1;
	while (dy <= 1)
	{
		dx = -1;
		while (dx <= 1)
		{
			if (dx == 0 && dy == 0)
				dx++;
			if (is_door_at(data, px + dx, py + dy))
			{
				if (is_facing_door(data))
				{
					data->can_open_door = 1;
					return ;
				}
			}
			dx++;
		}
		dy++;
	}
}
