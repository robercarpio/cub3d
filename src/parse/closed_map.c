/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   closed_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarpio-mamaratr <rcarpio-mamaratr@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 12:03:31 by rcarpio-mam       #+#    #+#             */
/*   Updated: 2026/02/05 18:04:05 by rcarpio-mam      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static char	**dup_map(char **map)
{
	int		height;
	char	*dup_line;
	int		i;
	char	**dup_map;
	
	height = map_height(map);
	dup_map = (char **)malloc(sizeof(char *)* height) + 1;
	if (!dup_map)
		return (NULL);
	i = -1;
	while (map[++i])
	{
		dup_line = ft_strdup(map[i]);
		dup_map[i] = dup_line;
	}
	dup_map[i] = NULL;
}

static int	flood_fill_closed(char **map, int x, int y, int *i)
{
	int	width;
	int	height;

	width = line_len(map[0]);
	height = map_height(map);
	if (x < 0 || y < 0 || x >= width || y >= height
		|| map[y][x] == '1')
		return (0);
	if (map[y][x] == 'C')
		(*i)++;
	if (map[y][x] == 'V')
		return (0);
	map[y][x] = 'V';
	return (flood_fill_closed(map, y, x + 1, i)
		|| flood_fill_closed(map, y, x - 1, i)
		|| flood_fill_closed(map, y + 1, x, i)
		|| flood_fill_closed(map, y - 1, x, i));
}

int	closed_map(t_data data)
{
    int i;

    i = 0;
    if (flood_fill_closed(data.map->map, data.player.x, data.player.y, &i))
        return (1);
    else
        return (0);
}