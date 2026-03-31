/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaratr <mamaratr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 12:30:46 by rcarpio-mam       #+#    #+#             */
/*   Updated: 2026/03/31 13:58:04 by mamaratr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static int	valid_neighbor(char c)
{
	return (c == '1' || c == '0' || c == 'D'
		|| c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

int	player_inside_map(char **map, int height)
{
	int	x;
	int	y;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == 'N' || map[y][x] == 'S'
				|| map[y][x] == 'E' || map[y][x] == 'W')
			{
				if (y == 0 || y >= height - 1)
					return (0);
				if (x == 0 || x + 1 >= (int)ft_strlen(map[y]))
					return (0);
				if (x >= (int)ft_strlen(map[y - 1])
					|| x >= (int)ft_strlen(map[y + 1]))
					return (0);
				if (!valid_neighbor(map[y - 1][x])
					|| !valid_neighbor(map[y + 1][x])
					|| !valid_neighbor(map[y][x - 1])
					|| !valid_neighbor(map[y][x + 1]))
					return (0);
			}
			x++;
		}
		y++;
	}
	return (1);
}

int	check_player(char **map)
{
	int	count;
	int	x;
	int	y;

	count = 0;
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == 'N' || map[y][x] == 'S'
				|| map[y][x] == 'E' || map[y][x] == 'W')
				count++;
			x++;
		}
		y++;
	}
	return (count == 1);
}

int	parse(t_data *data)
{
	if (!player_inside_map(data->map->map, data->map->m_height))
	{
		printf("Error: Player outside map boundaries.\n");
		return (0);
	}
	if (!check_player(data->map->map))
	{
		printf("Error: Invalid player count.\n");
		return (0);
	}
	if (!check_chars(data->map->map))
	{
		printf("Error: Invalid characters in the map.\n");
		return (0);
	}
	else
	{
		if (!closed_map(*data))
		{
			printf("Error: Map not closed.\n");
			return (0);
		}
	}
	init_player(data);
	return (1);
}
