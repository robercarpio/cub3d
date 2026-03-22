/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaratr <mamaratr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 16:27:54 by rcarpio-mam       #+#    #+#             */
/*   Updated: 2026/02/22 09:46:43 by mamaratr         ###   ########.fr       */
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

char	**expand_map(t_map map)
{
	char	**new_map;
	int		i;

	if (map.m_height <= 0 || map.m_width <= 0)
		return (NULL);
	new_map = malloc((map.m_height + 1) * sizeof(char *));
	if (!new_map)
		return (NULL);
	i = 0;
	while (i < map.m_height)
	{
		new_map[i] = ft_strjoin(" ", expand_line(map.map[i], map.m_width, ' '));
		if (!new_map[i])
		{
			while (--i >= 0)
				free(new_map[i]);
			free(new_map);
			return (NULL);
		}
		i++;
	}
	new_map[i] = fill_str(' ', map.m_width + 1);
	new_map[++i] = NULL;
	return (new_map);
}
