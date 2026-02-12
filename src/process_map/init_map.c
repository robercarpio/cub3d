/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaratr <mamaratr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 14:45:57 by rcarpio-mam       #+#    #+#             */
/*   Updated: 2026/02/12 12:00:20 by mamaratr         ###   ########.fr       */
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
	printf("Sale \n");
	return (map);
}
