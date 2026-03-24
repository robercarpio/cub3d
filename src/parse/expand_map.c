/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaratr <mamaratr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 16:27:54 by rcarpio-mam       #+#    #+#             */
/*   Updated: 2026/03/24 11:40:32 by mamaratr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static char	*expand_line(char *str, int max_len, char fill)
{
	int		i;
	char	*line;

	if (!str || max_len <= 0)
		return (NULL);
	line = malloc(max_len + 2);
	if (!line)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		line[i] = str[i];
		i++;
	}
	while (i < max_len)
	{
		line[i] = fill;
		i++;
	}
	line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

static void	free_map_partial(char **map, int i)
{
	while (--i >= 0)
		free(map[i]);
	free(map);
}

char	**expand_map(t_map map)
{
	char	**new_map;
	char	*tmp;
	int		i;

	if (map.m_height <= 0 || map.m_width <= 0)
		return (NULL);
	new_map = malloc((map.m_height + 2) * sizeof(char *));
	if (!new_map)
		return (NULL);
	i = 0;
	while (i < map.m_height)
	{
		tmp = expand_line(map.map[i], map.m_width, ' ');
		new_map[i] = ft_strjoin(" ", tmp);
		free(tmp);
		if (!new_map[i])
			return (free_map_partial(new_map, i), NULL);
		i++;
	}
	new_map[i] = fill_str(' ', map.m_width + 1);
	new_map[++i] = NULL;
	return (new_map);
}
