/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   closed_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarpio-mamaratr <rcarpio-mamaratr@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 12:03:31 by rcarpio-mam       #+#    #+#             */
/*   Updated: 2026/02/10 15:11:52 by rcarpio-mam      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static int	flood_fill_closed(char **map, int y, int x)
{
	int	width;
	int	height;

	width = line_len(map[0]);
	height = map_height(map);
	if (x < 0 || y < 0 || x >= width || y >= height
		|| map[y][x] == '1' || map[y][x] == 'V' || map[y][x] == '\n' || map[y][x] == '\t' )
		return (0);	
	if (map[y][x] == '0')
		return (1);
	map[y][x] = 'V';
	return (flood_fill_closed(map, y, x + 1) 
		|| flood_fill_closed(map, y, x - 1)
		|| flood_fill_closed(map, y + 1, x)
		|| flood_fill_closed(map, y - 1, x));
}

static t_coords sea_coords(char **map)
{
	int			x;
	int			y;
	t_coords	coords;

	y = -1;
	while(map[++y])
	{
		x = -1;
		while (map[y][++x])
		{
			if (map[y][x] == ' ')
			{
				coords.y = y;
				coords.x = x;
				return (coords);
			}
		}
	}
	coords.y = -1;
	// coords.x = -1;
	return (coords);
}

int	closed_map(t_data data)
{
	t_coords	coords;
	char		**map_expand;
	int			r_ff;
	map_expand = expand_map(*data.map);
	coords = sea_coords(map_expand);
	r_ff = 0;
	while (coords.y > -1 && r_ff == 0)
	{
		r_ff = flood_fill_closed(map_expand, coords.y, coords.x);
		print_arr(map_expand);
		coords = sea_coords(map_expand);
		printf("\ny:%d\n",coords.y);
		printf("x:%d\n",coords.x);
		printf("r_ff:%d\n",r_ff);
	}
	if (r_ff == 1)
		return (0);
	else
		return (1);
}
