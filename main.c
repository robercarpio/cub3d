/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarpio-mamaratr <rcarpio-mamaratr@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 10:44:11 by mamaratr          #+#    #+#             */
/*   Updated: 2026/01/22 12:40:32 by rcarpio-mam      ###   ########.fr       */
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

int	ft_init(t_data *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		return (0);
	data->keys = ft_calloc(MAX_KEYCODE, sizeof(int));
	if (!data->keys)
		return (0);
	return (1);
}

int	game_loop(t_data *data)
{
	if (data->keys[W])
		move_forward(data, UP);
	if (data->keys[S])
		move_forward(data, DOWN);
	if (data->keys[A])
		move_strafe(data, LEFT);
	if (data->keys[D])
		move_strafe(data, RIGHT);
	if (data->keys[KEY_LEFT])
		rotate_player(data, -ROT_SPEED);
	if (data->keys[KEY_RIGHT])
		rotate_player(data, ROT_SPEED);

	clear_image(data);
	draw_map(data);
	draw_player(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);

	return (0);
}

// int	load_test_map(t_data *data)
// {
// 	data->map->m_height = 5;
// 	data->map->m_width = 10;

// 	data->map->map = malloc(sizeof(char *) * 6);
// 	if (!data->map->map)
// 		return (0);

// 	data->map->map[0] = ft_strdup("1111111111");
// 	data->map->map[1] = ft_strdup("1000000001");
// 	data->map->map[2] = ft_strdup("10P0000001");
// 	data->map->map[3] = ft_strdup("1000000001");
// 	data->map->map[4] = ft_strdup("1111111111");
// 	data->map->map[5] = NULL;

// 	data->map->m_height = 5;
// 	data->map->m_width = 10;
// 	data->textures.floor = "0x00AAAAAA";
// 	data->textures.celling = "0x005555FF";

// 	return (1);
// }

int	main(int argc, char **argv)
{
	t_data	data;
	t_map	map;
	
	(void)argv;
	if (argc != 2)
	{
		printf("Error!\nUsage: ./cub3d <map.cub>\n");
		return (0);
	}
	if (!ft_alloc_data(&data, &map))
		return (0);
	if (!ft_init(&data))
		return (0);
	// if (!load_test_map(&data))
	// 	return (0);
	map = init_map(file_to_arr(argv[1]));
	init_player(&data);
	data.win = mlx_new_window(data.mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "CUB3D");
	if (!data.win)
		return (0);
	data.img.img = mlx_new_image(data.mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	data.img.addr = mlx_get_data_addr(data.img.img, &data.img.bpp,
			&data.img.line_length, &data.img.endian);
	mlx_hook(data.win, 2, 1L << 0, key_press, &data);
	mlx_hook(data.win, 3, 1L << 1, key_release, &data);
	mlx_hook(data.win, 17, 0, ft_exit, &data);
	mlx_loop_hook(data.mlx, game_loop, &data);
	mlx_loop(data.mlx);
	return (0);
}


// int	main (int argc, char *argv[])
// {
// 	if (argc == 2)
// 	{
// 		if (cub_file(argv[1]))
// 			play(argv[1]);
// 		else
// 			printf("Error: Invalid file extension.\nUsage: %s <map_file.ber>\n", argv[0]);

// 	}	

// 	else
// 		printf("Error: Invalid number of arguments.\nUsage: %s <map_file>\n", argv[0]);
// 	return (0);
// }