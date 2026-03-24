/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaratr <mamaratr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 17:30:39 by rcarpio-mam       #+#    #+#             */
/*   Updated: 2026/03/24 12:35:21 by mamaratr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

char	*fill_str(char c, int width)
{
	int		i;
	char	*str;

	str = malloc(width + 1);
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
		return (free(arr), NULL);
	i = -1;
	while (++i < height)
	{
		arr[i + 1] = ft_strdup(map[i]);
		if (!arr[i + 1])
		{
			while (--i >= 0)
				free(arr[i + 1]);
			free(arr[0]);
			return (free(arr), NULL);
		}
	}
	arr[i + 1] = NULL;
	return (arr);
}
