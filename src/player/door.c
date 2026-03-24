/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaratr <mamaratr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 11:02:09 by mamaratr          #+#    #+#             */
/*   Updated: 2026/03/24 12:37:33 by mamaratr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	is_door_at(t_data *data, int x, int y)
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

void	toggle_door(char *row, int x)
{
	if (row[x] == 'D')
		row[x] = 'd';
	else
		row[x] = 'D';
}

int	is_facing_door(t_data *data)
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

static int	check_adjacent_door(t_data *data, int px, int py)
{
	int	dx;
	int	dy;

	dy = -1;
	while (dy <= 1)
	{
		dx = -1;
		while (dx <= 1)
		{
			if ((dx || dy) && is_door_at(data, px + dx, py + dy)
				&& is_facing_door(data))
				return (1);
			dx++;
		}
		dy++;
	}
	return (0);
}

void	check_door_proximity(t_data *data)
{
	data->can_open_door = check_adjacent_door(data, (int)data->player.x,
			(int)data->player.y);
}
