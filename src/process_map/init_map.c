/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaratr <mamaratr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2026/02/10 13:53:01 by mamaratr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	get_texture_id(char *str)
{
	if (!ft_strncmp(str, "NO", 2))
		return (TEX_NORTH);
	if (!ft_strncmp(str, "SO", 2))
		return (TEX_SOUTH);
	if (!ft_strncmp(str, "WE", 2))
		return (TEX_WEST);
	if (!ft_strncmp(str, "EA", 2))
		return (TEX_EAST);
	return (-1);
}

void	skip_textures(char	***file)
{
	while (**file)
	{
		if(get_texture_id(**file) != -1)
			(*file)++;
		else if (**file[0] == 'F' || **file[0] == 'C')
			(*file)++;
		else if (**file[0] == '\n')
			(*file)++;
		else
			break;
	}
}


t_map	init_map(char **file)
{
	t_map	map;
	char	**tmp;

	tmp = file;
	skip_textures(&tmp);
	map.map = allocate_map(tmp);
	map.m_width = map_width(map.map);
	map.m_height = map_height(map.map);
	return (map);
}
