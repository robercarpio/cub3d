/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaratr <mamaratr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 11:03:07 by rcarpio-cye       #+#    #+#             */
/*   Updated: 2026/02/12 12:10:22 by mamaratr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void print_map(t_map map)
{
	int i;
	
	i = 0;
	while (map.map[i])
	{
		printf("%s", map.map[i]);
		i++;
	}
}

void	print_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		printf("%s",arr[i]);
		i++;
	}
}

void	play (char *route)
{
	//char	**file;
	t_data	data;
	t_map	map;
	
	if (!cub_file(route))
		printf("Error!\nInvalid map file\nUsage: ./cub3d <map.cub>\n");
	else
	{
		ft_alloc_data(&data, &map);
		ft_init(&data, route);
		// *data.map = init_map(file);
		parse(data);
	}
}

