/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaratr <mamaratr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 14:45:57 by rcarpio-mam       #+#    #+#             */
/*   Updated: 2026/02/22 09:51:50 by mamaratr         ###   ########.fr       */
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

unsigned int	get_color(char *str)
{
	char			**split;
	unsigned int	color;
	int				i;

	split = ft_split(str + 1, ',');
	if (!split || !split[0] || !split[1] || !split[2])
		return (0);
	color = 0;
	color |= ((unsigned char)ft_atoi(split[0])) << 16;
	color |= ((unsigned char)ft_atoi(split[1])) << 8;
	color |= ((unsigned char)ft_atoi(split[2]));
	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
	return (color);
}

void	skip_textures(char	***file, t_map *map)
{
	while (**file)
	{
		if (get_texture_id(**file) != -1)
			(*file)++;
		else if ((**file)[0] == 'F')
		{
			map->floor_color = get_color(**file);
			(*file)++;
		}
		else if ((**file)[0] == 'C')
		{
			map->ceiling_color = get_color(**file);
			(*file)++;
		}
		else if (**file[0] == '\n')
			(*file)++;
		else
			break ;
	}
}

t_map	init_map(char **file)
{
	t_map	map;
	char	**tmp;

	ft_bzero(&map, sizeof(t_map));
	tmp = file;
	skip_textures(&tmp, &map);
	map.map = allocate_map(tmp);
	map.m_width = map_width(map.map);
	map.m_height = map_height(map.map);
	return (map);
}
