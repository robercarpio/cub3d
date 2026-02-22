/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaratr <mamaratr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 10:44:11 by mamaratr          #+#    #+#             */
/*   Updated: 2026/02/22 10:35:11 by mamaratr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	ft_exit(t_data *data)
{
	if (data)
	{
		if (data->mlx && data->win)
			mlx_destroy_window(data->mlx, data->win);
	}
	exit(EXIT_SUCCESS);
	return (0);
}

int	ft_alloc_data(t_data *data, t_map *map)
{
	ft_bzero(data, sizeof(t_data));
	ft_bzero(map, sizeof(t_map));
	data->map = map;
	return (1);
}

int	main(int argc, char *argv[])
{
	if (argc == 2)
		play(argv[1]);
	else
		printf("Error!\nInvalid map file\nUsage: ./cub3d <map.cub>\n");
	return (0);
}
