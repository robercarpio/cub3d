/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarpio-mamaratr <rcarpio-mamaratr@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 14:45:57 by rcarpio-mam       #+#    #+#             */
/*   Updated: 2026/01/18 15:11:02 by rcarpio-mam      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static int  is_texture(char *str)
{
	if (ft_strcmp(ft_substr(str,0,2),"NO")==0)
		return (1);
	else if (ft_strcmp(ft_substr(str,0,2),"SO")==0)
		return (2);
	else if(ft_strcmp(ft_substr(str,0,2),"WE")==0)
		return (3);
	else if (ft_strcmp(ft_substr(str,0,2),"EA")==0)
		return (4);
	else
		return (0);
}

static void	skip_textures(char	**file)
{
	while (is_texture(*file))
		file++;
	while (*file[0] == '\n')
		file++;
	while (*file[0] == 'F' || *file[0] == 'C')
		file++;
	while (*file[0] == '\n')
		file++;
	
}

t_map   init_map(char **file)
{
    t_map	map;
	char	**tmp;

	tmp = file;
	skip_textures(&tmp);
	map.map = allocate_map(tmp);
	map.m_width = 0;
	map.m_height = 0;
	return (map);
}
