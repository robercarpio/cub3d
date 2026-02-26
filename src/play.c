/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaratr <mamaratr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 11:03:07 by rcarpio-cye       #+#    #+#             */
/*   Updated: 2026/02/26 13:36:57 by mamaratr         ###   ########.fr       */
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

void	clear_image(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < SCREEN_HEIGHT)
	{
		x = 0;
		while (x < SCREEN_WIDTH)
		{
			my_mlx_pixel_put(&data->img, x, y, 0x000000);
			x++;
		}
		y++;
	}
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
	check_door_proximity(data);
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
	mlx_mouse_hide(data->mlx, data->win);
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
	data->map = malloc(sizeof(t_map));
	if (!data->map)
		return (0);
	*data->map = init_map(file);
	init_player(data);
	data->msg_e.img = mlx_xpm_file_to_image(data->mlx, "img/pressE.xpm",
			&data->msg_e.width, &data->msg_e.height);
	if (data->msg_e.img)
		data->msg_e.addr = mlx_get_data_addr(data->msg_e.img, &data->msg_e.bpp,
				&data->msg_e.line_length, &data->msg_e.endian);
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
		if(parse(data))
			start_window(&data);
	}
}

