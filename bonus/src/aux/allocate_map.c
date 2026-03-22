/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaratr <mamaratr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 17:30:39 by rcarpio-mam       #+#    #+#             */
/*   Updated: 2026/02/22 09:42:04 by mamaratr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

char	*fill_str(char c, int width)
{
	int		i;
	char	*str;

	str = malloc(width);
	if (!str)
		return (NULL);
	i = -1;
	while (++i < width)
		str[i] = c;
	str[i] = '\0';
	return (str);
}

// char    **allocate_map(char **map)
// {
//     char    **arr;
//     int     height;
//     int     i;
//
//     height = map_height(map) + 1;
//     arr = (char **)malloc((height+1)*sizeof(char *));
//     i = 0;
//     arr[i] = fill_str(' ', map_width(map));
//     while(map[++i])
//         arr[i] = map[i];
//     arr[height] = NULL;
//     return (arr);
// }

char	**allocate_map(char **map)
{
	char	**arr;
	int		height;
	int		i;

	height = map_height(map);
	arr = malloc((height + 2) * sizeof(char *));
	if (!arr)
		return (NULL);
	arr[0] = fill_str(' ', map_width(map));
	if (!arr[0])
		return (NULL);
	i = 0;
	while (i < height)
	{
		arr[i + 1] = map[i];
		i++;
	}
	arr[i + 1] = NULL;
	return (arr);
}
