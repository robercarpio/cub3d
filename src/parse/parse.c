/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaratr <mamaratr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 12:30:46 by rcarpio-mam       #+#    #+#             */
/*   Updated: 2026/02/22 09:47:30 by mamaratr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static int	count_players(char **map)
{
	int	i;
	int	j;
	int	count;

	count = 0;
	i = -1;
	while (++i)
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'P')
				count++;
			j++;
		}
	}
	return (count);
}

int	parse(t_data data)
{
	if (!check_chars(data.map->map))
	{
		printf("Error: Invalid characters in the map.\n");
		return (0);
	}
	if (count_players(data.map->map) != 1)
		printf("Error: n player\n");
	else
	{
		if (closed_map(data))
			printf("bien\n");
		else
		{
			printf("mal\n");
			return (0);
		}
	}
	return (1);
}
