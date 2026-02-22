/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_dimmenssions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaratr <mamaratr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 13:02:43 by rcarpio-mam       #+#    #+#             */
/*   Updated: 2026/02/22 09:43:09 by mamaratr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	line_len(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	map_height(char **map)
{
	int	i;

	i = -1;
	while (map[++i])
		;
	return (i);
}

int	map_width(char **map)
{
	int	i;
	int	max_len;

	i = -1;
	max_len = 0;
	while (map[++i])
	{
		if (line_len(map[i]) > max_len)
			max_len = line_len(map[i]);
	}
	return (max_len);
}
