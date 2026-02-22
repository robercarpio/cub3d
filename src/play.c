/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaratr <mamaratr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 11:03:07 by rcarpio-cye       #+#    #+#             */
/*   Updated: 2026/02/19 10:08:24 by mamaratr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

// void	print_map(t_map map)
// {
// 	int	i;

// 	i = 0;
// 	while (map.map[i])
// 	{
// 		printf("%s", map.map[i]);
// 		i++;
// 	}
// }

// void	print_arr(char **arr)
// {
// 	int	i;

// 	i = 0;
// 	while (arr[i])
// 	{
// 		printf("%s", arr[i]);
// 		i++;
// 	}
// }

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
	ft_render_frame(data);
	return (0);
}

static void	start_window(t_data *data)
{
	data->win = mlx_new_window(data->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "CUB3D");
	data->img.img = mlx_new_image(data->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	data->img.addr = mlx_get_data_addr(data->img.img, &data->img.bpp,
			&data->img.line_length, &data->img.endian);
	mlx_hook(data->win, 2, 1L << 0, key_press, data);
	mlx_hook(data->win, 3, 1L << 1, key_release, data);
	mlx_hook(data->win, 6, 1L << 6, mouse_move, data);
	mlx_hook(data->win, 17, 0, ft_exit, data);
	mlx_loop_hook(data->mlx, game_loop, data);
	mlx_mouse_move(data->mlx, data->win, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	mlx_loop(data->mlx);
}

int	ft_init(t_data *data, char *route)
{
	char	**file;

	data->mlx = mlx_init();
	if (!data->mlx)
		return (0);
	data->width = SCREEN_WIDTH;
	data->height = SCREEN_HEIGHT;
	data->keys = ft_calloc(MAX_KEYCODE, sizeof(int));
	if (!data->keys)
		return (0);
	file = file_to_arr(route);
	init_textures(file, data);
	parse_textures(file, data);
	load_textures(data);
	data->map = malloc(sizeof(t_map));
	if (!data->map)
		return (0);
	*data->map = init_map(file);
	init_player(data);
	start_window(data);
	return (1);
}

void	play(char *route)
{
	t_data	data;
	t_map	map;

	if (!cub_file(route))
		printf("Error!\nInvalid map file\nUsage: ./cub3d <map.cub>\n");
	else
	{
		ft_alloc_data(&data, &map);
		ft_init(&data, route);
		parse(data);
	}
}
