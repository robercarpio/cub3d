/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarpio-mamaratr <rcarpio-mamaratr@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 16:27:54 by rcarpio-mam       #+#    #+#             */
/*   Updated: 2026/01/21 15:09:00 by rcarpio-mam      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static char	*expand_line(char *line, int new_width)
{
	char	*new_line;
	int		i;

	i = 0;
	new_line = (char *)malloc((new_width + 1) * sizeof(char));
	if (!new_line)
		return (NULL);
	while (line[i])
	{
		new_line[i] = line[i];
		i++;
	}
	while (i < new_width)
	{
		new_line[i] = '*';
		i++;
	}
	new_line[i] = '\0';
	return (new_line);
}

char	**expand_map(t_map map)
{
	char	**new_map;
	int 	i;

	new_map = (char **)malloc(map.m_height * sizeof(char *));
	i = 0;
	if (!new_map)
		return (NULL);
	while (map.map[i])
	{
		new_map[i] = expand_line(map.map[i], map.m_width);
		if (!new_map[i])
			return (NULL);
		i++;
	}
	return (new_map);
}
