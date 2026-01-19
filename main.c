/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarpio-mamaratr <rcarpio-mamaratr@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 10:44:11 by mamaratr          #+#    #+#             */
/*   Updated: 2026/01/16 12:19:07 by rcarpio-mam      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	main (int argc, char *argv[])
{
	if (argc == 2)
	{
		if (cub_file(argv[1]))
			play(argv[1]);
		else
			printf("Error: Invalid file extension.\nUsage: %s <map_file.ber>\n", argv[0]);

	}	

	else
		printf("Error: Invalid number of arguments.\nUsage: %s <map_file>\n", argv[0]);
	return (0);
}

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

// int	ft_alloc_data(t_data *data, t_map *map)
// {
// 	ft_bzero(data, sizeof(t_data));
// 	ft_bzero(map, sizeof(t_map));
// 	data->map = map;
// 	return (1);
// }

// int	ft_init(t_data *data)
// {
// 	data->mlx = mlx_init();
// 	if (!data->mlx)
// 		return (0);
// 	data->keys = ft_calloc(MAX_KEYCODE, sizeof(int));
// 	if (!data->keys)
// 		return (0);
// 	return (1);
// }

// int	main(int argc, char **argv)
// {
// 	t_data	data;
// 	t_map	map;
	
// 	(void)argv;
// 	if (argc != 2)
// 	{
// 		printf("Error!\nUsage: ./cub3d <map.cub>\n");
// 		return (0);
// 	}
// 	if (!ft_alloc_data(&data, &map))
// 		return (0);
// 	if (!ft_init(&data))
// 		return (0);
// 	data.win = mlx_new_window(data.mlx, 1200, 800, "CUB3D");
// 	if (!data.win)
// 		return (0);
// 	mlx_hook(data.win, 2, 1L << 0, key_press, &data);
// 	mlx_hook(data.win, 3, 1L << 1, key_release, &data);
// 	mlx_hook(data.win, 17, 0, ft_exit, &data);
// 	mlx_loop(data.mlx);
// 	return (0);
// }