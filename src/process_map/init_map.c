/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaratr <mamaratr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 14:45:57 by rcarpio-mam       #+#    #+#             */
/*   Updated: 2026/02/06 12:04:53 by mamaratr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	get_texture_id(char *str)
{
	if (!ft_strncmp(str, "NO", 3))
		return (TEX_NORTH);
	if (!ft_strncmp(str, "SO", 3))
		return (TEX_SOUTH);
	if (!ft_strncmp(str, "WE", 3))
		return (TEX_WEST);
	if (!ft_strncmp(str, "EA", 3))
		return (TEX_EAST);
	return (-1);
}

void	skip_textures(char	***file)
{
	while (is_texture(**file))
		(*file)++;
	while (**file[0] == '\n')
		(*file)++;
	while (**file[0] == 'F' || **file[0] == 'C')
		(*file)++;
	while (**file[0] == '\n')
		(*file)++;
	
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
